#include "minishell.h"

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (0);
}

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
	// ft_putstr_fd(ft_find_env_var("PWD"), 1);
	// ft_putstr_fd(" ", 1); // TODO: сделать отображение дириктории
	ft_putstr_fd("\033[0;92m(⌐■_■)☞ \033[0m$ ", 1);
}

// обработчик сигналов (ничего не делает)
void	ft_sighnd(int signo)
{
	(void)signo;
	ft_putstr_fd("^C", 1);
	// ft_putstr_fd("\n", 0); // ! не работает
	exit(1);
}
