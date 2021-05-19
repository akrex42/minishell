#include "minishell.h"

void	ft_print_env(void)
{
	char **beg_env = g_all.env;
	while (*g_all.env != NULL)
	{
		char *this_env = *g_all.env;
		char *equal = ft_strchr(this_env, '=');
		if (equal == NULL)
		{
			printf("%s%s%c", "declare -x ", this_env, '\n');
		}
		else
		{
			printf("%s", "declare -x ");
			printf("%s", ft_substr(this_env, 0, ft_strlen(this_env) - ft_strlen(equal)));
			printf("%c", equal[0]);
			printf("%c", '"');
			printf("%s", ft_substr(equal, 1, ft_strlen(equal) - 1));
			printf("%c%c", '"', '\n');
		}
		g_all.env++;
	}
	g_all.env = beg_env;
}

void	ft_chdir_emdash(char *dir, char **beg_env, char *this_env, char *equal)
{
	getcwd(dir, 1000); // THEY ARE NOT WELL-ORDERED IN THIS CASE
	chdir(getenv("OLDPWD")); // we get the env variable oldpwd and change dir to there
	beg_env = g_all.env;
	while (*g_all.env != 0)
	{
		this_env = *g_all.env;
		equal = ft_strchr(this_env, '=');
		if (!(ft_strncmp(equal, "OLDPWD", 6)))
		{
			this_env = *g_all.env;
			*g_all.env = ft_strjoin("PWD=", ft_substr(equal, 1, ft_strlen(equal) - 1));
			free(this_env);
		}
		else if (!(ft_strncmp(equal, "PWD", 3)))
		{
			this_env = *g_all.env;
			*g_all.env = ft_strjoin("OLDPWD=", ft_substr(equal, 1, ft_strlen(equal) - 1));
			free(this_env);
		}
		g_all.env++;
	}
	g_all.env = beg_env;
}

void	ft_chdir_normal(char **beg_env, char *dir, char *dir1, char *this_env, char *equal)
{
	beg_env = g_all.env;
	while (*g_all.env != 0)
	{
		this_env = *g_all.env;
		equal = ft_substr(this_env, 0, ft_strlen(this_env) - ft_strlen(ft_strchr(this_env, '=')));
		if (!(ft_strncmp(equal, "PWD", 3)))
		{
			this_env = *g_all.env;
			*g_all.env = ft_strjoin("PWD=", dir1);
			free(this_env);
			free(equal);
		}
		else if (!(ft_strncmp(equal, "OLDPWD", 6)))
		{
			this_env = *g_all.env;
			*g_all.env = ft_strjoin("OLDPWD=", dir);
			free(this_env);
			free(equal);
		}
		else
			free(equal);
		g_all.env++;
	}
	g_all.env = beg_env;
}

int 	ft_cd(char **str)
{
	char *equal;
	char *this_env;
	char **beg_env;
	char dir[1000];
	char dir1[1000];
	// g_all.env = ft_allocate_env(envp); // we need to initialize it somewhere else
	if (str[1] != NULL)
	{
		if ((strcmp(str[1], "-"))) //DO WE NEED TO MAKE TILDA?????
		{
			getcwd(dir, 1000);
			if (chdir(str[1]) == -1) //we get the env variable home and change dir to there
			{
				ft_putstr_fd("bash: cd: ", 1);
				ft_putstr_fd(str[1], 1);
				ft_putstr_fd(": No such file or directory", 1);
				ft_putchar_fd('\n', 1);
				return (1);
			}
			getcwd(dir1, 1000);
			ft_chdir_normal(beg_env, dir, dir1, this_env, equal);
		}
		else
			ft_chdir_emdash(dir, beg_env, this_env, equal);
	}
	ft_print_env();
	return (0);
	// sleep (1000);
}

// int 	main(int argc, char **argv, char **envp)
// {
// 	ft_cd(argv);
// 	return (0);
// }