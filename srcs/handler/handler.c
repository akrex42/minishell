#include "minishell.h"

// * пример вызова программы
// * исполняемые файлы искать в $PATH
// char *arg[] = {"cat", NULL};
// execve("/bin/cat", arg, NULL);

// * если команды не существует на вход следующей ничего не передается
void	ft_execute(void) //TODO: передавать лист из пайпов
{
	// TODO: добавлять / к названию программы
	// char	prog[] = "cat"; // название программы
	// char	*arg[] = {prog, NULL}; // Сюда будет писаться имя программы и АРГУМЕНТЫ
	int		fd[2];
	int		ret;
	int		pid;
	char	*str;
	char	*tmp;
	int		i;

	//TODO: зациклить форк и передавать данные от процесса к  процессу
	//TODO: разобраться что делать если в цепочке пайпов неверная программа --  выдать ошибку, что нет такой программы?
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		close(fd[1]);
		ft_reset_input_mode();
		if (ft_is_relative()) // относительный путь (c /)
		{
			if (execve(g_all.commands->prog, g_all.commands->args, NULL))
			{
				strerror(errno);
				return ;
			}
		}
		else
		{
			tmp = ft_strjoin("/", g_all.commands->prog);
			if (execve(tmp, g_all.commands->args, NULL))
			{
				strerror(errno);
				return ;
			}
			i = 0;
			while (g_all.path[i] != NULL && ret == -1)
			{
				str = ft_strjoin(g_all.path[i], tmp);
				if (execve(str, g_all.commands->args, NULL))
				{
					free(str);
					strerror(errno);
					return ;
				}
				i++;
				free(str);
			}
		}
		exit(127); // return?
	}
	signal(SIGINT, SIG_IGN); // игнарировать сигналы во время выполнения программ
	waitpid(pid, &ret, 0);
	signal(SIGINT, ft_sighnd); //ctrl + с // возвращаем первоначый обработчик
	ret = WEXITSTATUS(ret); // получение возвращаемого значения
	g_all.exit_status = ret; // как присваивать правильно???
	ft_set_input_mode(&g_all);
	// TODO: добавить обработчик выходных сигналов
	ft_error_handler(ret);
	if (ret != 127)
	{
		ft_putstr_fd("exit status = ", 1);
		ft_putnbr_fd(ret, 1);
		ft_putchar_fd('\n', 1);
	}
	close(fd[1]);
	close(fd[0]);
}

// делает из лексем лист исполняемых файлов
void	ft_syntax_analyzer(void)
{
	// если всего один аргумент
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

// | - передает вывод одной программы на вход другой
// $? - exit status variable (содержит код последней команды)
int	ft_execute_builtins()
{

	int ret;
	// ft_putstr_fd(g_all.env[0], 1);

	ret = 3;
	if (!ft_strncmp("cd", g_all.commands->prog, 3))
		ret = ft_cd(g_all.commands->args);
	else if (!ft_strncmp("echo", g_all.commands->prog, 5))
		ret = ft_echo(g_all.commands->args);
	else if (!ft_strncmp("env", g_all.commands->prog, 4))
		ret = ft_env(g_all.commands->args);
	else if (!ft_strncmp("exit", g_all.commands->prog, 5))
		ret = ft_exit(g_all.commands->args);
	else if (!ft_strncmp("export", g_all.commands->prog, 7))
		ret = ft_export(g_all.commands->args);
	else if (!ft_strncmp("pwd", g_all.commands->prog, 4))
		ret = ft_pwd(g_all.commands->args);
	else if (!ft_strncmp("unset", g_all.commands->prog, 6))
		ret = ft_unset(g_all.commands->args);
	return (ret); // $?
}

// static void	ft_print_env()
// {
// 	int	i;
// 	char *equal;

// 	i = 0;
// 	while (g_all.env[i] != NULL)
// 	{
// 		equal = ft_strchr(g_all.env[i], '=');
// 		if (equal == NULL)
// 		{
// 			ft_putstr_fd("declare -x ", 1);
// 			ft_putstr_fd(g_all.env[i], 1);
// 			ft_putchar_fd('\n', 1);
// 		}
// 		else
// 		{
// 			ft_putstr_fd("declare -x ", 1);
// 			ft_putstr_fd(ft_substr(g_all.env[i], 0, ft_strlen(g_all.env[i]) - ft_strlen(equal)), 1);
// 			ft_putchar_fd(equal[0], 1);
// 			ft_putchar_fd('"', 1);
// 			ft_putstr_fd(ft_substr(equal, 1, ft_strlen(equal) - 1), 1);
// 			ft_putchar_fd('"', 1);
// 			ft_putchar_fd('\n', 1);
// 		}
// 		i++;
// 	}
// }

void	ft_handler(void)
{
	//! если в названии программы есть '/' то нужно обрабатывать как директорию???

	//заглушка от пустых строк
	if (!(g_all.tokens))
		return ;
	ft_syntax_analyzer();
	ft_display_comands(); // ! для отладки
	// while (g_all.commands->next != NULL)
	// {
		if (ft_execute_builtins() == 3)
		{
			ft_execute();
		}
		// ft_print_env();
	// 	g_all.commands = g_all.commands->next;
	// }
	
}
