#include "minishell.h"

void	ft_close_file_fd(void)
{
	if (g_all.fd_in != -1 && !(g_all.commands->prev != NULL 
		&& g_all.commands->prev->special[0] == '|'))
	{
		close(g_all.fd_in);
		g_all.fd_in = -1;
	}
	// if (g_all.fd_in != -1 && !(g_all.commands->prev != NULL && fd1[0] != -1 &&
	// 	g_all.commands->prev->special[0] == '|'))
	// {
	// 	close(g_all.fd_in);
	// 	g_all.fd_in = -1;
	// }
	if (g_all.fd_out != -1 && !(g_all.commands->next != NULL &&
		g_all.commands->special[0] == '|'))
	{
		close(g_all.fd_out);
		g_all.fd_out = -1;
	}
}

int	ft_check_builtins(void)
{
	if (g_all.commands->prog != NULL && (!ft_strncmp("cd", 
			g_all.commands->prog, 3) || !ft_strncmp("echo", 
			g_all.commands->prog, 5) ||
		!ft_strncmp("env", g_all.commands->prog, 4) ||
		!ft_strncmp("exit", g_all.commands->prog, 5) ||
		!ft_strncmp("export", g_all.commands->prog, 7) ||
		!ft_strncmp("pwd", g_all.commands->prog, 4) ||
		!ft_strncmp("unset", g_all.commands->prog, 6)))
			return (1);
	return (0);
}

void	ft_execute_builtins(void)
{
	if (!ft_strncmp("cd", g_all.commands->prog, 3))
		g_all.exec.ret = ft_cd(g_all.commands->args);
	else if (!ft_strncmp("echo", g_all.commands->prog, 5))
		g_all.exec.ret = ft_echo(g_all.commands->args);
	else if (!ft_strncmp("env", g_all.commands->prog, 4))
		g_all.exec.ret = ft_env(g_all.commands->args);
	else if (!ft_strncmp("exit", g_all.commands->prog, 5))
		g_all.exec.ret = ft_exit(g_all.commands->args);
	else if (!ft_strncmp("export", g_all.commands->prog, 7))
		g_all.exec.ret = ft_export(g_all.commands->args);
	else if (!ft_strncmp("pwd", g_all.commands->prog, 4))
		g_all.exec.ret = ft_pwd(g_all.commands->args);
	else if (!ft_strncmp("unset", g_all.commands->prog, 6))
		g_all.exec.ret = ft_unset(g_all.commands->args);
}

void	ft_close_pipes(void)
{
	int	i;

	i = 0;
	while (g_all.pipes[i])
	{
		close(g_all.pipes[i][0]);
		close(g_all.pipes[i][1]);
		i++;
	}
}

// из fd1 - берем в fd2 - записываем
void	ft_execute_program(int *fd1, int *fd2, int i)
{
	if (g_all.commands->special[0] == '>' ||
		g_all.commands->special[0] == '<')
				return ; // оставить для того, чтобы последний редирект не выполнился
	// if (g_all.commands->prev != NULL)
	// 	if (g_all.commands->prev->prog == NULL)
	// 	{
	// 		close(g_all.fd_out);
	// 		g_all.fd_out = -1;
	// 	}
	if (!(g_all.pid[i][0] = fork()))
	{
		if (ft_check_builtins())
		{
			if (g_all.commands->next != NULL &&
				g_all.commands->special[0] == '|')
				g_all.fd_out = fd2[1];
			else if (g_all.fd_out == -1)
				g_all.fd_out = 1;
			ft_execute_builtins();
			if (g_all.commands->next != NULL &&
				g_all.commands->special[0] == '|')
				close(fd2[1]);
			else if (g_all.fd_out != 1)
				close(g_all.fd_out);
			g_all.exit_status = g_all.exec.ret;
			exit (g_all.exit_status);
		}
		// для ввода
		if (g_all.commands->prev != NULL &&
			g_all.commands->prev->special[0] == '|')
			dup2(fd1[0], 0);
		else if (g_all.fd_in != -1)
		{
			dup2(g_all.fd_in, 0);
			close(g_all.fd_in);
		}

		//для вывода
		if (g_all.commands->next != NULL &&
			g_all.commands->special[0] == '|')
			dup2(fd2[1], 1);
		else if (g_all.fd_out != -1)
		{
			dup2(g_all.fd_out ,1);
			close(g_all.fd_out);
		}
		ft_close_pipes();

		if (ft_is_relative())
			execve(g_all.commands->prog, g_all.commands->args, g_all.env);
		else
		{
			ft_rewrite_path();
			g_all.exec.tmp = ft_strjoin("/", g_all.commands->prog);
			i = 0;
			if (!g_all.path)
				exit(2);
			while (g_all.path[i] != NULL)
			{
				g_all.exec.str = ft_strjoin(g_all.path[i], g_all.exec.tmp);
				execve(g_all.exec.str, g_all.commands->args, g_all.env);
				i++;
				free(g_all.exec.str);
			}
			free(g_all.exec.tmp);
		}
		exit(errno);
	}
	close(fd1[0]);
	close(fd1[1]);
	ft_close_file_fd();
}

int	ft_redirect_error(void)
{
	ft_putstr_fd("my_bash: ", 2);
	ft_putstr_fd(g_all.commands->prog, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	g_all.exit_status = 1;
	return (-1);
}

int	ft_make_redirect_fd(void)
{
	t_comands_list	*tmp;

	tmp = g_all.commands;
	while (1)
	{
		if (!ft_strncmp(g_all.commands->special, ">>", 3) && !(g_all.commands->used))
		{
			if (g_all.fd_out != -1)
				close(g_all.fd_out);
			g_all.fd_out = open(g_all.commands->prog, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
			if (g_all.fd_out == -1 && errno != 14)
				return (ft_redirect_error());
			g_all.commands->used = 1;
		}
		else if (g_all.commands->special[0] == '>' && !(g_all.commands->used))
		{
			if (g_all.fd_out != -1)
				close(g_all.fd_out);
			g_all.fd_out = open(g_all.commands->prog, O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
			if (g_all.fd_out == -1 && errno != 14)
				return (ft_redirect_error());
			g_all.commands->used = 1;
		}
		else if (g_all.commands->special[0] == '<' && !(g_all.commands->used))
		{
			if (g_all.fd_in != -1)
				close(g_all.fd_in);
			g_all.fd_in = open(g_all.commands->prog, O_RDONLY, NULL);
			if (g_all.fd_in == -1 && errno != 14)
				return (ft_redirect_error());
			g_all.commands->used = 1;
		}
		if (g_all.commands->next == NULL)
			break ;
		g_all.commands = g_all.commands->next;
	}
	g_all.commands = tmp;
	return (0);
}

void	ft_skip_redirect(void)
{
	while ((g_all.commands->used == 1 || (g_all.commands->special[0] == '|' && g_all.commands->prog == NULL)) &&
			g_all.commands->next)
		g_all.commands = g_all.commands->next;
}

int	ft_count_progs(void)
{
	int	i;

	i = 0;
	ft_commands_go_beginning();
	while (g_all.commands)
	{
		ft_skip_redirect();
		if (g_all.commands->special[0] == '>'
			|| g_all.commands->special[0] == '<')
			break ;
		if (g_all.commands->prog != NULL)
			i++;
		if (g_all.commands->next != NULL)
			g_all.commands = g_all.commands->next;
		else
			break ;
	}
	ft_commands_go_beginning();
	return (i);
}

void	ft_make_pipes(void)
{
	int	i;

	i = ft_count_progs();
	g_all.pipes = malloc(sizeof(int*) * (i + 2));
	g_all.pipes[i + 1] = NULL; 
	while (i >= 0)
	{
		g_all.pipes[i] = malloc(sizeof(int) * 2);
		pipe(g_all.pipes[i]);
		i--;
	}
}

void	ft_make_pid(void)
{
	int	i;

	i = ft_count_progs();
	g_all.pid = malloc(sizeof(int*) * (i + 1));
	g_all.pid[i] = NULL;
	i--;
	while (i >= 0)
	{
		g_all.pid[i] = malloc(sizeof(int) * 1);
		g_all.pid[i][0] = -1;
		i--;
	}
}

void	ft_free_pid(void)
{
	int	i;

	i = 0;
	while (g_all.pid[i])
	{
		free(g_all.pid[i]);
		i++;
	}
	free(g_all.pid[i]);
	free(g_all.pid);
}

void	ft_free_pipes(void)
{
	int	i;

	i = 0;
	while (g_all.pipes[i])
	{
		free(g_all.pipes[i]);
		i++;
	}
	free(g_all.pipes[i]);
	free(g_all.pipes);
}

void	ft_go_to_right_prog(int i)
{
	int	j;

	j = 0;
	ft_commands_go_beginning();
	while (j != i)
	{
		ft_skip_redirect();
		if (g_all.commands->special[0] == '>'
			|| g_all.commands->special[0] == '<')
			break ;
		if (g_all.commands->prog == NULL)
		{
			g_all.commands = g_all.commands->next;
			continue ;
		}
		j++;
		g_all.commands = g_all.commands->next;
	}
}

void	ft_wait_pid(void)
{
	int	i;

	if (!g_all.pid)
		return ;
	i = 0;
	while (g_all.pid[i])
	{
		if (g_all.pid[i][0] != -1)
		{
			waitpid(g_all.pid[i][0], &g_all.exec.ret, 0);
			g_all.exec.ret = WEXITSTATUS(g_all.exec.ret);
			ft_go_to_right_prog(i);
			ft_error_handler(g_all.exec.ret);
		}
		i++;
	}
}

void	ft_execute(void)
{
	int		i;

	g_all.fd_in = -1;
	g_all.fd_out = -1;
	g_all.pipes = NULL;
	g_all.pid = NULL;
	if (ft_make_redirect_fd() == -1)
		return ;
	ft_make_pipes();
	ft_make_pid();
	signal(SIGINT, ft_sighnd_exec);
	signal(SIGQUIT, ft_sighnd_exec);
	ft_reset_input_mode();
	ft_skip_redirect();
	i = 0;
	if (ft_count_progs() == 1 && ft_check_builtins())
	{
		if (g_all.fd_out == -1)
			g_all.fd_out = 1;
		ft_execute_builtins();
	}
	else while (g_all.pipes) //условие на первое вхождение
	{
		ft_skip_redirect();
		ft_execute_program(g_all.pipes[i], g_all.pipes[i + 1], i);
		i++;
		if (g_all.commands->next == NULL)
			break;
		else
			g_all.commands = g_all.commands->next;
	}
	ft_wait_pid();
	ft_set_input_mode(&g_all);
	signal(SIGINT, ft_sighnd);
	signal(SIGQUIT, ft_sighnd);
	ft_free_pipes();
	ft_free_pid();
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
			if (g_all.commands->prog == NULL)
			{
				if (g_all.tokens->next != NULL)
				{
					ft_tokens_step_front();
					g_all.commands->prog = ft_strdup(g_all.tokens->content);
				}
			}
			else
			{
				ft_new_prog_node();
				ft_strlcpy(g_all.commands->special, g_all.commands->prev->special, 3);
				if (g_all.tokens->next != NULL)
				{
					ft_tokens_step_front();
					g_all.commands->prog = ft_strdup(g_all.tokens->content);
				}
				ft_bzero(g_all.commands->prev->special, 3);
			}
		}
		ft_tokens_step_front();
	}
	//если последний аргумент один // workd weirdly
	if (g_all.tokens->prev->prev != NULL)
		if (g_all.tokens->next == NULL && (g_all.commands->special[0] == '|' ||
			g_all.tokens->prev->prev->content[0] == '>' ||
			g_all.tokens->prev->prev->content[0] == '<'))
	{
		ft_tokens_step_front();
		ft_new_prog_node();
		ft_comands_list_add_args_and_prog();
	}
}

void	ft_move_redirect(void) // разделяет аргументы и редиректы
{
	t_tokens_list	*token;

	ft_tokens_to_beginning();
	while (1)
	{
		if (g_all.tokens->next != NULL)
			if ((g_all.tokens->content[0] == '>' ||
				g_all.tokens->content[0] == '<') &&
				!ft_comp_to_spec(g_all.tokens->next->next) &&
				g_all.tokens->prev != NULL)
			{ //!БЕЗУМИЕ
				token = g_all.tokens->next->next;
				g_all.tokens->prev->next = token;
				token->prev = g_all.tokens->prev;
				g_all.tokens->next->next = token->next;
				if (token->next != NULL)
					token->next->prev = g_all.tokens->next;
				token->next = g_all.tokens;
				g_all.tokens->prev = token;
				continue ;
			}
		if (g_all.tokens->next == NULL)
			break ;
		else
			g_all.tokens = g_all.tokens->next;
	}
}

void	ft_free_command_node(void)
{
	int	i;
	t_comands_list	*tmp;

	i = 0;
	while (g_all.commands->args[i])
	{
		free(g_all.commands->args[i]);
		i++;
	}
	free(g_all.commands->args[i]);
	free(g_all.commands->args);
	free(g_all.commands->prog);
	tmp = g_all.commands->next;
	g_all.commands = g_all.commands->prev;
	free(g_all.commands->next);
	g_all.commands->next = tmp;
	tmp->prev = g_all.commands;
}

void	ft_join_empty_redirect_2(void)
{
	while (1)
	{
		if (g_all.commands->special[0] != '>'
			&& g_all.commands->special[0] != '<'
			&& g_all.commands->special[0] != '|')
		{
			g_all.commands->special[0] = '|';
			g_all.commands->special[1] = '\0';
			g_all.commands->special[2] = '\0';
			break ;
		}
		if (g_all.commands->prev == NULL)
			break ;
		else
			g_all.commands = g_all.commands->prev;
	}
}

void	ft_join_empty_redirect(void)
{
	t_comands_list	*tmp;

	ft_commands_go_beginning();
	while (g_all.commands)
	{
		if (g_all.commands->special[0] == '|'
			&& g_all.commands->prog == NULL)
		{
			tmp = g_all.commands;
			ft_join_empty_redirect_2();
			if (g_all.commands->special[0] == '|'
				&& g_all.commands->prog != NULL)
			{
				g_all.commands = tmp;
				ft_free_command_node();
			}
			else
				g_all.commands = tmp;
		}
		if (g_all.commands->next == NULL)
			break ;
		else
			g_all.commands = g_all.commands->next;
	}
}

void	ft_handler(void)
{
	if (!(g_all.tokens))
		return ;
	ft_move_redirect(); // чтобы аргументы попадали в программу, даже если они разделены редиректами
	ft_syntax_analyzer();
	// ft_join_empty_redirect();
	// ft_display_comands(); // ! для отладки
	ft_commands_go_beginning();
	ft_execute();
}
