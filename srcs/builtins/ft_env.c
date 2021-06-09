#include "minishell.h"

static void	ft_print_env(char *equal)
{
	int		i;
	char	*key;
	char	*key1;

	i = 0;
	while (g_all.env[i] != NULL)
	{
		equal = ft_strchr(g_all.env[i], '=');
		if (equal != NULL)
		{
			key = ft_substr(g_all.env[i], 0,
					ft_strlen(g_all.env[i]) - ft_strlen(equal));
			ft_putstr_fd(key, g_all.fd_out);
			free(key);
			ft_putchar_fd(equal[0], g_all.fd_out);
			ft_putchar_fd('"', g_all.fd_out);
			key1 = ft_substr(equal, 1, ft_strlen(equal) - 1);
			ft_putstr_fd(key1, g_all.fd_out);
			free(key1);
			ft_putchar_fd('"', g_all.fd_out);
			ft_putchar_fd('\n', g_all.fd_out);
		}
		i++;
	}
}

void	ft_print_error_env(char *str)
{
	ft_putstr_fd("env: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": No such file or directory", 2);
	ft_putchar_fd('\n', 2);
}

int 	ft_env(char **str)
{
	char	*equal;
	int		i;

	i = 0;
	if (str[1] != NULL)
	{	
		ft_print_error_env(str[1]);
		return (1);
	}
	else
		ft_print_env(equal);
	return (0);
}
