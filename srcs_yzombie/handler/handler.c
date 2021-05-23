#include "minishell.h"

// из fd1 - берем в fd2 - записываем
void	ft_execute_programm(int *fd1, int *fd2)
{
	int	i;

	if (!fork())
	{
		// для ввода
		if (g_all.comands->prev != NULL && fd1[0] != -1) //TODO: перенести в отдельный файл
		{
			if (g_all.comands->prev->special[0] == '|')
				dup2(fd1[0], 0);
			// TODO: другие случаи
			close(fd1[0]);
			close(fd1[1]);
		}

		//для вывода
		if (g_all.comands->next != NULL && fd2[0] != -1) //TODO: перенести в отдельный файл
		{
			if (g_all.comands->special[0] == '|')
				dup2(fd2[1], 1);
			// TODO: другие случаи
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

	if (fd1[0] != -1) // для того, чтобы закончить рид
	{
		close(fd1[0]);
		close(fd1[1]);
	}

	waitpid(0, &g_all.exec.ret, 0);
	signal(SIGINT, ft_sighnd); //ctrl + с // возвращаем первоначый обработчик
	signal(SIGQUIT, ft_sighnd);
	ft_set_input_mode(&g_all);
	g_all.exec.ret = WEXITSTATUS(g_all.exec.ret);
	ft_error_handler(g_all.exec.ret); // TODO: выводить ошибки в стандарт аутпут
	//TODO: отлавить именно выход из программы на ctrl + c, а не просто его использование
	if (g_all.exit_status == 500)
		g_all.exec.ret = 130;
	if (g_all.exit_status == 501)
		g_all.exec.ret = 131;
	g_all.exit_status = g_all.exec.ret;
}

// * пример вызова программы
// char *arg[] = {"cat", NULL};
// execve("/bin/cat", arg, NULL);

void	ft_execute(void)
{
	// TODO: записать переменные в структуру
	int		i;
	int		fd1[2];
	int		fd2[2];

	fd1[0] = -1;
	fd2[0] = -1;
	while (1)
	{
		//TODO: разобраться что делать если в цепочке пайпов неверная программа
		//TODO: добавить buildins
		//TODO: закрывать пайпы в процессах

		pipe(fd1);
		ft_execute_programm(fd2, fd1);
		if (g_all.comands->next == NULL)
			break;
		else
			g_all.comands = g_all.comands->next;
		if (fd2[0] != -1)
		{
			close(fd2[0]);
			close(fd2[1]);
		}
		pipe(fd2);
		ft_execute_programm(fd1, fd2);
		//условие выхода из цикла
		if (g_all.comands->next == NULL)
			break;
		else
			g_all.comands = g_all.comands->next;
	} 
	//TODO: понять как закрывать fd'шники
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

// | - передает вывод одной программы на вход другой
// $? - exit status variable (содержит код последней команды)


void	ft_handler(void)
{
	//заглушка от пустых строк
	if (!(g_all.tokens))
		return ;
	ft_syntax_analyzer();
	// ft_display_comands(); // ! для отладки
	ft_commands_go_beginning();
	ft_execute();
}
