#include "minishell.h"

void	ft_close_file_fd(int *fd1, int *fd2)
{
	if (g_all.fd_in != -1 && !(g_all.comands->prev != NULL && fd1[0] != -1 &&
		g_all.comands->prev->special[0] == '|'))
	{
		close(g_all.fd_in);
		g_all.fd_in = -1;
	}
	if (g_all.fd_out != -1 && !(g_all.comands->next != NULL &&
		g_all.comands->special[0] == '|'))
	{
		close(g_all.fd_out);
		g_all.fd_out = -1;
	}
}

int	ft_check_builtins(void)
{
	if (!ft_strncmp("cd", g_all.comands->prog, 3) ||
		!ft_strncmp("echo", g_all.comands->prog, 5) ||
		!ft_strncmp("env", g_all.comands->prog, 4) ||
		!ft_strncmp("exit", g_all.comands->prog, 5) ||
		!ft_strncmp("export", g_all.comands->prog, 7) ||
		!ft_strncmp("pwd", g_all.comands->prog, 4) ||
		!ft_strncmp("unset", g_all.comands->prog, 6))
			return (1);
	return (0);
}

int	ft_execute_builtins(void)
{
	if (!ft_strncmp("cd", g_all.comands->prog, 3))
		g_all.exec.ret = ft_cd(g_all.comands->args);
	else if (!ft_strncmp("echo", g_all.comands->prog, 5))
		g_all.exec.ret = ft_echo(g_all.comands->args);
	else if (!ft_strncmp("env", g_all.comands->prog, 4))
		g_all.exec.ret = ft_env(g_all.comands->args);
	else if (!ft_strncmp("exit", g_all.comands->prog, 5))
		g_all.exec.ret = ft_exit(g_all.comands->args);
	else if (!ft_strncmp("export", g_all.comands->prog, 7))
		g_all.exec.ret = ft_export(g_all.comands->args);
	else if (!ft_strncmp("pwd", g_all.comands->prog, 4))
		g_all.exec.ret = ft_pwd(g_all.comands->args);
	else if (!ft_strncmp("unset", g_all.comands->prog, 6))
		g_all.exec.ret = ft_unset(g_all.comands->args);
	return (g_all.exec.ret);
}

// из fd1 - берем в fd2 - записываем
void	ft_execute_programm(int *fd1, int *fd2)
{
	int	i;

	if (g_all.comands->special[0] == '>' ||
		g_all.comands->special[0] == '<')
				return ;
	if (ft_check_builtins())
	{
		if (g_all.comands->next != NULL &&
			g_all.comands->special[0] == '|')
			g_all.fd_out = fd2[1];
		else if (g_all.fd_out == -1)
			g_all.fd_out = 1;
		ft_execute_builtins();
		if (g_all.comands->next != NULL &&
			g_all.comands->special[0] == '|')
			close(fd2[1]);
		else if (g_all.fd_out != 1)
			close(g_all.fd_out);
		g_all.exit_status = g_all.exec.ret;
		return ;
	}
	//builtins here
	if (!fork())
	{
		// для ввода
		if (g_all.comands->prev != NULL &&
			g_all.comands->prev->special[0] == '|')
			dup2(fd1[0], 0);
		else if (g_all.fd_in != -1)
		{
			dup2(g_all.fd_in, 0);
			close(g_all.fd_in);
		}
		if (fd1[0] != -1)
		{
			close(fd1[0]);
			close(fd1[1]);
		}

		//для вывода
		if (g_all.comands->next != NULL &&
			g_all.comands->special[0] == '|')
			dup2(fd2[1], 1);
		else if (g_all.fd_out != -1)
		{
			dup2(g_all.fd_out ,1);
			close(g_all.fd_out);
		}
		close(fd2[0]);
		close(fd2[1]);


		ft_reset_input_mode();
		if (ft_is_relative()) // относительный путь (c /)
			execve(g_all.comands->prog, g_all.comands->args, g_all.env);
		else
		{
			g_all.exec.tmp = ft_strjoin("/", g_all.comands->prog);
			i = 0;
			while (g_all.path[i] != NULL)
			{
				g_all.exec.str = ft_strjoin(g_all.path[i], g_all.exec.tmp);
				execve(g_all.exec.str, g_all.comands->args, g_all.env);
				i++;
				free(g_all.exec.str); // ! утечка, но можно не освобождать
			}
			free(g_all.exec.tmp);
		}
		exit(errno);
	}
	signal(SIGINT, ft_sighnd_exec); // сигналы во время выполнения программ
	signal(SIGQUIT, ft_sighnd_exec);

	if (fd1[0] != -1)
	{
		close(fd1[0]);
		close(fd1[1]);
	}
	ft_close_file_fd(fd1, fd2);

	waitpid(0, &g_all.exec.ret, 0);
	signal(SIGINT, ft_sighnd); //ctrl + с // возвращаем первоначый обработчик
	signal(SIGQUIT, ft_sighnd);
	ft_set_input_mode(&g_all);
	g_all.exec.ret = WEXITSTATUS(g_all.exec.ret);
	ft_error_handler(g_all.exec.ret); //TODO: в 2 fd
}

void	ft_make_redirect_fd(void)
{
	t_comands_list	*tmp;
	tmp = g_all.comands;
	while (1)
	{
		if (!ft_strncmp(g_all.comands->special, ">>", 3) && !(g_all.comands->used))
		{
			if (g_all.fd_out != -1)
				close(g_all.fd_out);
			g_all.fd_out = open(g_all.comands->prog, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
			if (g_all.fd_out == -1)
				exit(-1);
			g_all.comands->used = 1;
		}
		else if (g_all.comands->special[0] == '>' && !(g_all.comands->used))
		{
			if (g_all.fd_out != -1)
				close(g_all.fd_out);
			g_all.fd_out = open(g_all.comands->prog, O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
			if (g_all.fd_out == -1)
				exit(-1);
			g_all.comands->used = 1;
		}
		else if (g_all.comands->special[0] == '<' && !(g_all.comands->used))
		{
			if (g_all.fd_in != -1)
				close(g_all.fd_in);
			g_all.fd_in = open(g_all.comands->prog, O_RDONLY, NULL);
			if (g_all.fd_in == -1) //TODO: ОБРАБОТАТЬ ОШИБКУ и ПОМЕНЯТЬ exit'ы
				exit(-1);
			g_all.comands->used = 1;
		}
		if (g_all.comands->special[0] == ';' ||
			g_all.comands->next == NULL)
			break ;
		g_all.comands = g_all.comands->next;
	}
	g_all.comands = tmp;
}

void	ft_execute(void)
{
	// TODO: записать переменные в структуру
	int		i;
	int		fd1[2];
	int		fd2[2];

	fd1[0] = -1;
	fd2[0] = -1;
	g_all.fd_in = -1;
	g_all.fd_out = -1;
	while (1)
	{
		pipe(fd1);
		ft_make_redirect_fd();
		ft_execute_programm(fd2, fd1);
		if (g_all.comands->next == NULL)
			break;
		else
			g_all.comands = g_all.comands->next;
		pipe(fd2);
		ft_make_redirect_fd();
		ft_execute_programm(fd1, fd2);
		//условие выхода из цикла
		if (g_all.comands->next == NULL)
			break;
		else
			g_all.comands = g_all.comands->next;
	} 
}

// делает из лексем лист исполняемых файлов
void	ft_syntax_analyzer(void)
{
	// если всего один аргумент
	ft_tokens_to_beginning();
	if (g_all.tokens->next == NULL)
	{
		ft_new_prog_node();
		ft_comands_list_add_args_and_prog();
		return ;
	}
	while (g_all.tokens->next != NULL)
	{
		ft_new_prog_node();
		ft_comands_list_add_args_and_prog();
		
		if (ft_compare_prog_to_redirect())
		{
			if (g_all.comands->prog == NULL)
			{
				if (g_all.tokens->next != NULL)
				{
					ft_tokens_step_front();
					g_all.comands->prog = ft_strdup(g_all.tokens->content);
				}
			}
			else
			{
				ft_new_prog_node();
				ft_strlcpy(g_all.comands->special, g_all.comands->prev->special, 3);
				if (g_all.tokens->next != NULL)
				{
					ft_tokens_step_front();
					g_all.comands->prog = ft_strdup(g_all.tokens->content);
				}
				ft_bzero(g_all.comands->prev->special, 3);
			}
		}
		ft_tokens_step_front();
	}
	//если последний аргумент один
	if (g_all.tokens->prev->prev != NULL)
		if (g_all.tokens->next == NULL && (g_all.comands->special[0] == '|' ||
			g_all.comands->special[0] == ';' ||
			g_all.tokens->prev->prev->content[0] == '>' ||
			g_all.tokens->prev->prev->content[0] == '<'))
	{
		ft_tokens_step_front();
		ft_new_prog_node();
		ft_comands_list_add_args_and_prog();
	}
}

void	ft_handler(void)
{
	//заглушка от пустых строк
	if (!(g_all.tokens))
		return ;
	if (ft_syntax_error()) //TODO: в 2 fd ДОРАБОТАТЬ
		return ;
	ft_syntax_analyzer();
	// ft_display_comands(); // ! для отладки
	ft_commands_go_beginning(); // ! потом убрать
	ft_execute();
}
