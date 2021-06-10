#include "minishell.h"

int	ft_pwd(char **str)
{
	char	dir[1000];

	(void)str;
	getcwd(dir, 1000);
	ft_putstr_fd(dir, g_all.fd_out);
	ft_putchar_fd('\n', g_all.fd_out);
	return (0);
}
