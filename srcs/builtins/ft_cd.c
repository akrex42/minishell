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
// 			ft_putstr_fd("declare -x ", g_all.fd_out);
// 			ft_putstr_fd(g_all.env[i], g_all.fd_out);
// 			ft_putchar_fd('\n', g_all.fd_out);
// 		}
// 		else
// 		{
// 			ft_putstr_fd("declare -x ", g_all.fd_out);
// 			ft_putstr_fd(ft_substr(g_all.env[i], 0, ft_strlen(g_all.env[i]) 
// 			- ft_strlen(equal)), g_all.fd_out);
// 			ft_putchar_fd(equal[0], g_all.fd_out);
// 			ft_putchar_fd('"', g_all.fd_out);
// 			ft_putstr_fd(ft_substr(equal, 1, 
// 			ft_strlen(equal) - 1), g_all.fd_out);
// 			ft_putchar_fd('"', g_all.fd_out);
// 			ft_putchar_fd('\n', g_all.fd_out);
// 		}
// 		i++;
// 	}
// }

int	ft_print_error_cd(char **str)
{
	ft_putstr_fd("my_bash: cd: ", 2);
	ft_putstr_fd(str[1], 2);
	ft_putstr_fd(": No such file or directory", 2);
	ft_putchar_fd('\n', 2);
	return (1);
}

int	ft_chdir_null(char *dir, char **beg_env, char *this_env, char *equal)
{
	char *dir1;

	if (ft_find_env_var("HOME") == NULL)
	{
		ft_putstr_fd("my_bash: cd: ", 2);
		ft_putstr_fd("HOME not set", 2);
		ft_putchar_fd('\n', 2);
		return (1);
	}
	else if (!ft_strncmp(ft_find_env_var("HOME"), "\0", 1))
	{
		chdir(getenv("HOME"));
	}
	else
	{
		chdir(ft_find_env_var("HOME"));
		if (chdir(ft_find_env_var("HOME")) == -1) // переделать
		{
			ft_putstr_fd("my_bash: cd: ", 2);
			ft_putstr_fd(ft_find_env_var("HOME"), 2);
			ft_putstr_fd(": No such file or directory", 2);
			ft_putchar_fd('\n', 2);
			return (1);
		}
	}
	// getcwd(dir1, 1000);
	beg_env = g_all.env;
	while (*g_all.env != 0)
	{
		this_env = *g_all.env;
		equal = ft_substr(this_env, 0, ft_strlen(this_env)
				- ft_strlen(ft_strchr(this_env, '=')));
		if (!(ft_strncmp(equal, "PWD", 3)))
		{
			this_env = *g_all.env;
			*g_all.env = ft_strjoin("PWD=", ft_find_env_var("HOME"));
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
	return (0);
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

	if (str[1] == NULL)
	{
		getcwd(dir, 1000);
		if (ft_chdir_null(dir, beg_env, this_env, equal))
		{
			return (1);
		}
	}
	else if (str[1] != NULL)
	{
		if ((strncmp(str[1], "-", 2)))
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
