#include "minishell.h"

void 	ft_cd(char **str, int argc, char **envp)
{
	// char *dir;
	char *newdir;
	char *this_env;
	char **beg_env;
	char *key1;
	int errno;

	char dir[1000]; //
	g_all.env = ft_allocate_env(envp); // we need to initialize it somewhere else
	beg_env = g_all.env;
	if (argc > 1)
	{
		if ((strcmp(str[1], "-"))) //DO WE NEED TO MAKE TILDA?????
		{
			getcwd(dir, 1000);
			if (chdir(str[1] == -1)); //we get the env variable home and change dir to there
			{
				print_err_cd(errno); //ERROR
			}
			while (*g_all.env != 0)
			{
				this_env = *g_all.env;
				char *equal = ft_strchr(this_env, '=');
				if (!(ft_strncmp(ft_substr(this_env, 0, ft_strlen(this_env) - ft_strlen(ft_strchr(this_env, '='))), "PWD", 3)))
				{
					// printf("%s\n", this_env);
					*g_all.env = ft_strjoin("PWD=", str[1]);
					// g_all.env + ft_strlen(this_env) - ft_strlen(ft_strchr(this_env, '=')) = ft_strdup(str[1]);
					g_all.env++;
				}
				else if (!(ft_strncmp(ft_substr(this_env, 0, ft_strlen(this_env) - ft_strlen(ft_strchr(this_env, '='))), "OLDPWD", 6)))
				{
					// printf("%s\n", this_env);
					*g_all.env = ft_strjoin("OLDPWD=", dir);
					// g_all.env + ft_strlen(this_env) - ft_strlen(ft_strchr(this_env, '=')) = ft_strdup(str[1]);
					g_all.env++;
				}
				else
					g_all.env++;
			}
			// g_all.env = beg_env;
			// while (*g_all.env != NULL)
			// {
			// 	this_env = *g_all.env;
			// 	char *equal = ft_strchr(this_env, '=');
			// 	if (equal == NULL)
			// 	{
			// 		printf("%s%s%c", "declare -x ", this_env, '\n');
			// 	}
			// 	else
			// 	{
			// 		printf("%s", "declare -x ");
			// 		printf("%s", ft_substr(this_env, 0, ft_strlen(this_env) - ft_strlen(equal)));
			// 		printf("%c", equal[0]);
			// 		printf("%c", '"');
			// 		printf("%s", ft_substr(equal, 1, ft_strlen(equal) - 1));
			// 		printf("%c%c", '"', '\n');
			// 	}
			// 	g_all.env++;
			// }
			// printf("%s\n", getcwd(dir, 1000));
		}
		else
		{
			getcwd(dir, 1000); // THEY ARE NOT WELL-ORDERED IN THIS CASE
			chdir(getenv("OLDPWD")); // we get the env variable oldpwd and change dir to there
			while (*g_all.env != 0)
			{
				this_env = *g_all.env;
				char *equal = ft_strchr(this_env, '=');
				if (!(ft_strncmp(ft_substr(this_env, 0, ft_strlen(this_env) - ft_strlen(ft_strchr(this_env, '='))), "OLDPWD", 6)))
				{
					// printf("%s\n", this_env);
					*g_all.env = ft_strjoin("PWD=", ft_substr(equal, 1, ft_strlen(equal) - 1));
					// g_all.env + ft_strlen(this_env) - ft_strlen(ft_strchr(this_env, '=')) = ft_strdup(str[1]);
					printf("%s\n", *g_all.env);
					g_all.env++;
				}
				else if (!(ft_strncmp(ft_substr(this_env, 0, ft_strlen(this_env) - ft_strlen(ft_strchr(this_env, '='))), "PWD", 3)))
				{
					// printf("%s\n", this_env);
					*g_all.env = ft_strjoin("OLDPWD=", ft_substr(equal, 1, ft_strlen(equal) - 1));
					// g_all.env + ft_strlen(this_env) - ft_strlen(ft_strchr(this_env, '=')) = ft_strdup(str[1]);
					printf("%s\n", *g_all.env);
					g_all.env++;
				}
				else
					g_all.env++;
			}
		}
	}
	else
	{
		chdir(getenv("HOME")); //we get the env variable home and change dir to there
		while (*g_all.env != 0)
		{
			this_env = *g_all.env;
			char *equal = ft_strchr(this_env, '=');
			if (!(ft_strncmp(ft_substr(this_env, 0, ft_strlen(this_env) - ft_strlen(ft_strchr(this_env, '='))), "PWD", 3)))
			{
				// printf("%s\n", this_env);
				*g_all.env = ft_strjoin("OLDPWD=", ft_substr(equal, 1, ft_strlen(equal) - 1));
				// g_all.env + ft_strlen(this_env) - ft_strlen(ft_strchr(this_env, '=')) = ft_strdup(str[1]);
				printf("%s\n", *g_all.env);
				g_all.env++;
			}
			else if (!(ft_strncmp(ft_substr(this_env, 0, ft_strlen(this_env) - ft_strlen(ft_strchr(this_env, '='))), "OLDPWD", 3)))
			{
				// printf("%s\n", this_env);
				*g_all.env = ft_strjoin("PWD=", getenv("HOME"));
				// g_all.env + ft_strlen(this_env) - ft_strlen(ft_strchr(this_env, '=')) = ft_strdup(str[1]);
				printf("%s\n", *g_all.env);
				g_all.env++;
			}
			else
				g_all.env++;
		}
	}
}

int 	main(int argc, char **argv, char **envp)
{
	ft_cd(argv, argc, envp);
	return (0);
}