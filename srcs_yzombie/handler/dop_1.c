#include "minishell.h"

int	ft_is_relative(void)
{
	if (ft_strrchr(g_all.comands->prog, '/') != NULL)
		return (1);
	return (0);	
}

void	ft_sighnd_exec(int signo)
{
	if (signo == 3) // ctrl + '\'
	{
		ft_putstr_fd("Quit: 3\n", 1);
		g_all.exit_status = 501;
	}
	else
		g_all.exit_status = 500; // используется как флаг для изменения этого значения после форка
}
