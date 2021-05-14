#include "minishell.h"

// * пример вызова программы
// * исполняемые файлы искать в $PATH
// char *arg[] = {"cat", NULL};
// execve("/bin/cat", arg, NULL);

//TODO: ft_pipes_redirect() которому передается количество вызываемых программ 
//TODO: и сами программы с аргументами (в каком виде ?) 

// * если команды не существует на вход следующей ничего не передается
void	ft_execute(void)
{
	// как искать исполняемые файлы???
	// 1 сначала проверить по билдинам
	// 2 потом в PATH (запускать по очереди со всеми путями)
	
	// * test
	//TODO: добавлять / к названию программы в зависимости от того, что там написано
	char prog[] = "/ls"; // название программы
	char *arg[] = {prog, NULL}; // Сюда будет писаться имя программы и АРГУМЕНТЫ
	int fd[2];
	int	ret;
	int pid;

	//TODO: зациклить форк и передавать данные от процесса к  процессу
	//TODO: разобраться что делать если в цепочке пайпов неверная программа
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		
		char	*str;
		int		i;
		close(fd[0]);
		ret = execve(prog, arg, NULL);
		i = 0;
		while (ret == -1 && g_all.path[i] != NULL)
		{
			str = ft_strjoin(g_all.path[i], prog);
			ret = execve(str, arg, NULL);
			i++;
			free(str);
		}
		exit(ret);
	}
	waitpid(pid, &ret, 0);
	g_all.exit_status = ret;
	if (ret == -1)
	{ 
		ft_putstr_fd(prog, 1);
		ft_putstr_fd(": No such file or directory\n", 1);
	}
	else
	{
		ft_putstr_fd("exit status = ", 1);
		ft_putnbr_fd(ret, 1);
		ft_putchar_fd('\n', 1);
	}
	close(fd[1]);
	close(fd[0]);
	// * end of test
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
	//TODO: 1) добавлять все исполняемые команды соедененные пайпами лист
	//TODO: 2) вызвать execute
	//! если в названии программы есть '/' то нужно обрабатывать как директорию??? 

	ft_execute();
	//работа с токенами
}