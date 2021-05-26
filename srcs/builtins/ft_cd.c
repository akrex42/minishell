#include "minishell.h"

// void	ft_print_env(void)
// {
// 	int	i;

// 	i = 0;
// 	while (g_all.env[i] != NULL)
// 	{
// 		char *equal = ft_strchr(g_all.env[i], '=');
// 		if (equal == NULL)
// 		{
// 			ft_putstr_fd("declare -x ", 1);
// 			ft_putstr_fd(g_all.env[i], 1);
// 			ft_putchar_fd('\n', 1);
// 		}
// 		else
// 		{
// 			ft_putstr_fd("declare -x ", 1);
// 			ft_putstr_fd(ft_substr(g_all.env[i], 0, ft_strlen(g_all.env[i]) 
// 			- ft_strlen(equal)), 1);
// 			ft_putchar_fd(equal[0], 1);
// 			ft_putchar_fd('"', 1);
// 			ft_putstr_fd(ft_substr(equal, 1, 
// 			ft_strlen(equal) - 1), 1);
// 			ft_putchar_fd('"', 1);
// 			ft_putchar_fd('\n', 1);
// 		}
// 		i++;
// 	}
// }

void	ft_print_error_cd(char **str)
{
	ft_putstr_fd("bash: cd: ", 1);
	ft_putstr_fd(str[1], 1);
	ft_putstr_fd(": No such file or directory", 1);
	ft_putchar_fd('\n', 1);
}

void	ft_chdir_emdash(char *dir, char **beg_env, char *this_env, char *equal)
{
	getcwd(dir, 1000);
	chdir(getenv("OLDPWD"));
	beg_env = g_all.env;
	while (*g_all.env != 0)
	{
		this_env = *g_all.env;
		equal = ft_strchr(this_env, '=');
		if (!(ft_strncmp(equal, "OLDPWD", 6)))
		{
			this_env = *g_all.env;
			*g_all.env = ft_strjoin("PWD=", ft_substr(equal, 1,
						ft_strlen(equal) - 1));
			free(this_env);
		}
		else if (!(ft_strncmp(equal, "PWD", 3)))
		{
			this_env = *g_all.env;
			*g_all.env = ft_strjoin("OLDPWD=", ft_substr(equal, 1,
						ft_strlen(equal) - 1));
			free(this_env);
		}
		g_all.env++;
	}
	g_all.env = beg_env;
}

void	ft_chdir_normal(char *dir, char *dir1, char *this_env, char *equal)
{
	char	**beg_env;

	beg_env = g_all.env;
	while (*g_all.env != 0)
	{
		this_env = *g_all.env;
		equal = ft_substr(this_env, 0, ft_strlen(this_env)
				- ft_strlen(ft_strchr(this_env, '=')));
		if (!(ft_strncmp(equal, "PWD", 3)))
		{
			this_env = *g_all.env;
			*g_all.env = ft_strjoin("PWD=", dir1);
			free(this_env);
		}
		else if (!(ft_strncmp(equal, "OLDPWD", 6)))
		{
			this_env = *g_all.env;
			*g_all.env = ft_strjoin("OLDPWD=", dir);
			free(this_env);
		}
		free(equal);
		g_all.env++;
	}
	g_all.env = beg_env;
}

int	ft_cd(char **str)
{
	char	*equal;
	char	*this_env;
	char	**beg_env;
	char	dir[1000];
	char	dir1[1000];

	// g_all.env = ft_allocate_env(envp);
	if (str[1] != NULL)
	{
		if ((strcmp(str[1], "-")))
		{
			getcwd(dir, 1000);
			if (chdir(str[1]) == -1)
			{
				ft_print_error_cd(str);
				return (1);
			}
			getcwd(dir1, 1000);
			ft_chdir_normal(dir, dir1, this_env, equal);
		}
		else
			ft_chdir_emdash(dir, beg_env, this_env, equal);
	}
	return (0);
}

/* int 	main(int argc, char **argv, char **envp)
{
	ft_cd(argv);
	return (0);
} */
