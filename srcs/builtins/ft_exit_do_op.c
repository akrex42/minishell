#include "minishell.h"

int	check_cond(void)
{
	if (g_all.commands->prev != NULL
		&& (g_all.commands->prev->special[0]
			&& g_all.commands->prev->special[0] == '|'))
		return (g_all.exec.ret);
	else
	{
		ft_putstr_fd("exit\n", g_all.fd_out);
		exit(g_all.exec.ret);
	}
	return (0);
}

int	ft_print_err_exit_return(char **str)
{
	ft_putstr_fd("my_bash: exit: ", 2);
	ft_putstr_fd(str[1], 2);
	ft_putstr_fd(": numeric argument required", 2);
	ft_putchar_fd('\n', 2);
	return (255);
}

void	ft_print_err_exit(char **str)
{
	ft_putstr_fd("my_bash: exit: ", 2);
	ft_putstr_fd(str[1], 2);
	ft_putstr_fd(": numeric argument required", 2);
	ft_putchar_fd('\n', 2);
	exit(255);
}
