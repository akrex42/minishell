#include "minishell.h"
// #include <errno.h> //errno
/* WE DON'T NEED TO USE FORK AS ALL THE PROCESSES ARE EXECUTED BY THE PARENT*/

void 	ft_cd(char **str, int argc, char **envp)
{
	// char *dir;
	char *newdir;
	char *this_env;
	char **beg_env;
	char *key1;

	char dir[1000]; // MAYBE WE SHOULD SOMEHOW ADD OLDPWD IN THE STRUCT EACH TIME WE CHANGE IT
	g_all.env = ft_allocate_env(envp); // we need to initialize it somewhere else
	beg_env = g_all.env;
	if ((strcmp(str[1], "-"))) //DO WE NEED TO MAKE TILDA?????
	{
		printf("Current directory is %s\n", getcwd(dir, 1000));
		printf("%d\n", chdir(str[1])); //we get the env variable home and change dir to there
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
			else if (!(ft_strncmp(ft_substr(this_env, 0, ft_strlen(this_env) - ft_strlen(ft_strchr(this_env, '='))), "OLDPWD", 3)))
			{
				// printf("%s\n", this_env);
				*g_all.env = ft_strjoin("OLDPWD=", dir);
				// g_all.env + ft_strlen(this_env) - ft_strlen(ft_strchr(this_env, '=')) = ft_strdup(str[1]);
				g_all.env++;
			}
			else
				g_all.env++;
		}
			g_all.env = beg_env;
	while (*g_all.env != NULL)
	{
		this_env = *g_all.env;
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
		printf("Current directory is %s\n", getcwd(dir, 1000));
	}
	else
	{
		printf("Current directory is %s\n", getcwd(dir, ft_strlen(dir)));
		printf("%d\n", chdir(getenv("OLDPWD"))); //we get the env variable oldpwd and change dir to there
		printf("Current directory is %s\n", getcwd(dir, ft_strlen(dir)));
	}

	//WE NEED TO WRITE A NEW VALUE TO THE KEY PWD AND OLDPWD!!!!
	
	// else
	// {
	// 	// if
	// 	// {
	// 	// 	getcwd(dir, 1000);
	// 	// 	newdir = ft_strjoin(dir, "/");
	// 	// 	newdir = ft_strjoin(newdir, str);
	// 	// 	if (chdir(newdir) == -1)
	// 	// 	{
	// 	// 		printf("%s", "error\n");
	// 	// 		return ;
	// 	// 	}
	// 	// 	printf("%d\n", chdir(newdir)); // if -1 then print error
	// 	// 	printf("Current directory is %s\n", newdir);
	// 	// }
	// }
}

int 	main(int argc, char **argv, char **envp)
{
	if (argc >= 2)
	{
		ft_cd(argv, argc, envp);
	}
	else if (argc == 1)
	{
		char dir[1000];
		printf("%d\n", chdir(getenv("HOME"))); //we get the env variable home and change dir to there
		getcwd(dir, 1000); //add realloc and errors
		printf("Current directory is %s", dir);
		// ft_cd(argv[0]);
	}
	return (0);
}