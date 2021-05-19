#include "minishell.h"

// * пример вызова программы
// * исполняемые файлы искать в $PATH
// char *arg[] = {"cat", NULL};
// execve("/bin/cat", arg, NULL);

// * если команды не существует на вход следующей ничего не передается
void	ft_execute(void) //TODO: передавать лист из пайпов
{
	// TODO: добавлять / к названию программы
	char	prog[] = "cat"; // название программы
	char	*arg[] = {prog, NULL}; // Сюда будет писаться имя программы и АРГУМЕНТЫ
	int		fd[2];
	int		ret;
	int		pid;
	char	*str;
	int		i;

	//TODO: зациклить форк и передавать данные от процесса к  процессу
	//TODO: разобраться что делать если в цепочке пайпов неверная программа
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		close(fd[1]);
		ft_reset_input_mode();
		char *test = ft_strjoin("/", prog);
		i = 0;
		while (g_all.path[i] != NULL)
		{
			str = ft_strjoin(g_all.path[i], test);
			ret = execve(str, arg, NULL);
			i++;
			free(str);
		}
		ret = 127;
		exit(ret);
	}
	signal(SIGINT, SIG_IGN); // игнарировать сигналы во время выполнения программ
	waitpid(pid, &ret, 0);
	ret = WEXITSTATUS(ret);
	signal(SIGINT, ft_sighnd); //ctrl + с // возвращаем первоначый обработчик
	ft_set_input_mode(&g_all);
	g_all.exit_status = ret; // как присваивать правильно???
	// TODO: добавить обработчик выходных сигналов
	if (ret == -1)
	{ 
		ft_putstr_fd(prog, 1);
		ft_putstr_fd(": No such file or directory\n", 1);
	}
	else if (ret == 127)
	{
		//программа не найдена
	}
	else
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


void	ft_handler(void)
{
	//! если в названии программы есть '/' то нужно обрабатывать как директорию???

	//заглушка от пустых строк
	if (!(g_all.tokens))
		return ;
	ft_syntax_analyzer();
	ft_display_comands(); // ! для отладки
	// ft_execute();
}
