#include "minishell.h"

void	ft_error_handler(int ret)
{
	if (ret == 127)
	{
		if (ft_is_relative())
		{
			ft_putstr_fd(g_all.commands->prog, 1);
			ft_putstr_fd(": No such file or directory\n", 1);
		}
		else
		{
			ft_putstr_fd(g_all.commands->prog, 1);
			ft_putstr_fd(": command not found\n", 1);
		}
	}
}
