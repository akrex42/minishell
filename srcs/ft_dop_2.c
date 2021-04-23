#include "main_term.h"

void	ft_malloc_error(void)
{
	printf("Malloc error\n");
	exit(2);
}

void	ft_file_open_error(void)
{
	printf("Can`t open history file\n");
	exit(3);
}

// устанавливает начальные символы
void	ft_set_prompt(void)
{
	write(1, "\033[0;92m(⌐■_■)☞ \033[0m$ ", 30);
}

// обработчик сигналов
void	ft_sighnd(int signo)
{
	(void)signo;
	printf("Signal function\n");
}
