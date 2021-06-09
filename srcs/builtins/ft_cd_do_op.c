#include "minishell.h"

int	ft_error(char *dir, char *this_env, char *equal, char **str)
{
	char	dir1[1000];

	getcwd(dir, 1000);
	if (chdir(str[1]) == -1)
	{
		ft_print_error_cd(str);
		return (1);
	}
	getcwd(dir1, 1000);
	ft_chdir_normal(dir, dir1, this_env, equal);
	return (0);
}

int	ft_home(void)
{
	if (ft_find_env_var("HOME") == NULL)
	{
		ft_putstr_fd("my_bash: cd: ", 2);
		ft_putstr_fd("HOME not set", 2);
		ft_putchar_fd('\n', 2);
		return (1);
	}
	else if (!ft_strncmp(ft_find_env_var("HOME"), "\0", 1))
		chdir(getenv("HOME"));
	else
	{
		chdir(ft_find_env_var("HOME"));
		if (chdir(ft_find_env_var("HOME")) == -1)
		{
			ft_putstr_fd("my_bash: cd: ", 2);
			ft_putstr_fd(ft_find_env_var("HOME"), 2);
			ft_putstr_fd(": No such file or directory", 2);
			ft_putchar_fd('\n', 2);
			return (1);
		}
	}
	return (0);
}
