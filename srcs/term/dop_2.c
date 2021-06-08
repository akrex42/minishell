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

void	ft_set_prompt(void)
{
	ft_putstr_fd("\033[0;92m(⌐■_■)☞ \033[0m$ ", 1);
}

void	ft_sighnd(int signo)
{
	if (signo == 3)
		return ;
	else
	{
		ft_putstr_fd("\n", 1);
		free(g_all.str);
		free(g_all.str_hist);
		ft_cycle_head();
		g_all.exit_status = 1;
	}
}
