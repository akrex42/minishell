#include "minishell.h"

static void	ft_print_env(char *equal)
{
	int	i;

	i = 0;
	char *key;
	char *key1;
	// ft_putstr_fd("THERE", 1);
	// ft_putstr_fd("ALSO THERE", 1);
	// ft_putstr_fd(g_all.env[1], 1);
	while (g_all.env[i] != NULL)
	{
		// ft_putstr_fd("ONE MORE", 1);
		equal = ft_strchr(g_all.env[i], '=');
		if (equal != NULL)
		{
			key = ft_substr(g_all.env[i], 0, ft_strlen(g_all.env[i]) - ft_strlen(equal));
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
	// g_all.env = ft_allocate_env(g_all.env);
	// ft_putstr_fd(*g_all.env, 1);

	if (str[1] != NULL)
	{	
		// printf("%s", "HERE");
		ft_print_error_env(str[1]);
		return (1);
	}
	else
	{
		// ft_putstr_fd("HERE", 1);
		// ft_putchar_fd('\n', 1);
		ft_print_env(equal);
	}
	return (0);
}

/* int main (int argc, char **argv, char **envp)
// {
// 	ft_env(argv, envp);
// 	return (0);
// } */

// PRINT ENVS!!!!!
