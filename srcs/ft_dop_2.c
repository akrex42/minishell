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
	char str[] = "\033[0;92m(⌐■_■)☞ \033[0m$ ";

	write(1, str, ft_strlen(str));
}
