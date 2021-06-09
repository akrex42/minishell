#include "minishell.h"

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
	if (ft_home())
		return (1);
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

	if (str[1] == NULL)
	{
		getcwd(dir, 1000);
		if (ft_chdir_null(dir, beg_env, this_env, equal))
			return (1);
	}
	else if (str[1] != NULL)
	{
		if ((strncmp(str[1], "-", 2)))
		{
			if (ft_error(dir, this_env, equal, str))
				return (1);
		}
		else
			ft_chdir_emdash(dir, beg_env, this_env, equal);
	}
	return (0);
}
