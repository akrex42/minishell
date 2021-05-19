#include "minishell.h"

void	ft_print_error_env(char *str)
{
	ft_putstr_fd("env: ", 1);
	ft_putstr_fd(str[1], 1);
	ft_putstr_fd(": No such file or directory", 1);
	ft_putchar_fd('\n', 1);
}

int 	ft_env(char **str)
{
	char *equal;
	char **beg_env;

	beg_env = g_all.env;
	// g_all.env = ft_allocate_env(envp);
	if (str[1] == NULL)
	{
		while (*g_all.env != 0)
		{
			equal = ft_strchr(*g_all.env, '=');
			if (equal == NULL)
				g_all.env++;
			ft_putstr_fd(*g_all.env, 1);
			ft_putchar_fd('\n', 1);
			g_all.env++;
		}
		g_all.env = beg_env;
	}
	else if (str[1] != NULL)
	{
		ft_print_error_env(str[1]);
		return(1);
	}
	return(0);
}

// int main (int argc, char **argv, char **envp)
// {
// 	ft_env(argv, envp);
// 	return (0);
// }