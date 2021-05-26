#include "minishell.h"

int	ft_check_and_execute_builtins(void)
{
	// ft_putstr_fd(g_all.env[0], 1);
	// ft_putstr_fd("here", 1);
	g_all.exec.ret = -1;
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
	return (g_all.exec.ret); // $?
}

void	ft_close_file_fd(void)
{
	if (g_all.fd_in != -1)
	{
		close(g_all.fd_in);
		g_all.fd_in = -1;
	}
	if (g_all.fd_out != -1)
	{
		close(g_all.fd_out);
		g_all.fd_out = -1;
	}
}

// из fd1 - берем в fd2 - записываем
void	ft_execute_programm(int *fd1, int *fd2)
{
	int	i;

	// ft_putstr_fd("here", 1);
	if (ft_check_and_execute_builtins() == -1)
	{
		g_all.flag_builtin = 0;
	}
	if (!fork())
	{
		// для ввода
		if (g_all.commands->prev != NULL && fd1[0] != -1) //TODO: перенести в отдельный файл
		{
			if (g_all.commands->prev->special[0] == '|')
				dup2(fd1[0], 0);
			
			// TODO: другие случаи
			close(fd1[0]);
			close(fd1[1]);
		}
		if (g_all.fd_in != -1)
		{
			dup2(g_all.fd_in ,0);
		}
		//для вывода
		if (g_all.commands->next != NULL && fd2[0] != -1) //TODO: перенести в отдельный файл
		{
			if (g_all.commands->special[0] == '|')
				dup2(fd2[1], 1);
			if (g_all.fd_out != -1)
				dup2(g_all.fd_out, 1);
			// TODO: другие случаи
			close(fd2[0]);
			close(fd2[1]);
		}
		// ft_putstr_fd("here", 1);
		ft_reset_input_mode();
		if (ft_is_relative() && (g_all.flag_builtin == 0)) // относительный путь (c /)
			execve(g_all.commands->prog, g_all.commands->args, g_all.env);
		else
		{
			g_all.exec.tmp = ft_strjoin("/", g_all.commands->prog);
			i = 0;
			while (g_all.path[i] != NULL)
			{
				g_all.exec.str = ft_strjoin(g_all.path[i], g_all.exec.tmp);
				execve(g_all.exec.str, g_all.commands->args, g_all.env);
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
	ft_close_file_fd();

	waitpid(0, &g_all.exec.ret, 0);
	signal(SIGINT, ft_sighnd); //ctrl + с // возвращаем первоначый обработчик
	signal(SIGQUIT, ft_sighnd);
	ft_set_input_mode(&g_all);
	g_all.exec.ret = WEXITSTATUS(g_all.exec.ret);
	ft_error_handler(g_all.exec.ret); //TODO: в 2 fd
}

// * пример вызова программы
// char *arg[] = {"cat", NULL};
// execve("/bin/cat", arg, NULL);

void	ft_make_redirect_fd(void)
{
	//TODO: убирать файлы, которые мы уже исопльзовали ??
	//TODO: добавить ПРАВИЛЬНЫЙ алгоритм
	if (g_all.commands->next != NULL)
	{
		if (!ft_strncmp(g_all.commands->special, ">>", 3))
		{
			g_all.fd_out = open(g_all.commands->next->prog, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU); //TODO: разобраться с доступом к файлу
			if (g_all.fd_out == -1)
				exit(-1);
		}
		else if (g_all.commands->special[0] == '>')
		{
			g_all.fd_out = open(g_all.commands->next->prog, O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
			if (g_all.fd_out == -1)
				exit(-1);
		}
		else if (g_all.commands->special[0] == '<') // 
		{
			g_all.fd_in = open(g_all.commands->next->prog, O_RDONLY | O_TRUNC | O_CREAT, S_IRWXU);
			g_all.flag_restart = 1;
			if (g_all.fd_in == -1)
				exit(-1); // here restart the cycle 
		}
	}
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
		if (g_all.flag_restart == 1)
		{
			ft_commands_go_beginning();
			g_all.flag_restart = 0;
		}
		// ft_putstr_fd("here", 1);
		ft_execute_programm(fd2, fd1);
		if (g_all.commands->next == NULL || g_all.commands->special[0] == '<')
			break;
		else
			g_all.commands = g_all.commands->next;
		pipe(fd2);
		ft_make_redirect_fd();
		ft_execute_programm(fd1, fd2);
		//условие выхода из цикла
		if (g_all.commands->next == NULL || g_all.commands->special[0] == '<')
			break;
		else
			g_all.commands = g_all.commands->next;
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
		ft_tokens_go_next_spec();
	}
	//если последни	аргумент один
	g_all.tokens = g_all.tokens->prev;
	if (g_all.tokens->next->next == NULL &&
		ft_compare_tokens_cont_to_spec())
	{
		g_all.tokens = g_all.tokens->next;
		ft_new_prog_node();
		ft_comands_list_add_args_and_prog();
	}
}

// < - меняет standart input (0) на содержимое файла (прга < файл)
// елси идет (прога < файл < файл < файл ...) то на вход подается содержимое только последнего файла

// > - записывает вывод предыдущей прогрраммы в файл, есил файла нет создет его
// елси идет (прога > файл > файл > файл ...) то выход записывается только в последний файл
//! СОДЕРЖИМОЕ ПРЕДЫДУЩИХ ФАЙЛОВ СТИРАЕТСЯ

// >> - записывает вывод в файл, но не перезаписывает его, а добавляет содержимое
// елси идет (прога >> файл >> файл >> файл ...) то выход записывается только в последний файл
//! СОДЕРЖИМОЕ ПРЕДЫДУЩИХ ФАЙЛОВ ОСТАЕТСЯ

//TODO: перепрверить входы такого плана (grep Makefile < aaa > test < test1)

void	ft_handler(void)
{
	//заглушка от пустых строк
	if (!(g_all.tokens))
		return ;
	ft_syntax_analyzer();
	ft_display_comands(); // ! для отладки
	ft_commands_go_beginning(); // ! потом убрать
	if (ft_syntax_error()) //TODO: в 2 fd
		return ;
	ft_execute();
}
