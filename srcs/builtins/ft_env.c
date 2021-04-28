#include "minishell.h"

void 	ft_env(const char *str, char **envp)
{
//	int fd;
	char *equal;
	char *this_env;

	g_all.env = ft_allocate_env(envp);
	// char **env = g_all.env;
	while (*g_all.env != 0)
	{
		this_env = *g_all.env;
		equal = ft_strchr(this_env, '=');
		if (equal == NULL)
		{
			g_all.env++;
		}
		printf("%s\n", this_env);
		g_all.env++;
	}
}

int main (int argc, char **argv, char **envp)
{
	if (argc == 1)
	{
		ft_env(argv[0], envp);
	}
	else if (argc > 1)
	{
		printf("%s%s%s", "env: ", argv[1],": no such file or directory" );
		return (-1);
		//PERMISSION DENIED CASES AND WHEN $HOME -- WHAT SHALL WE DO? 
		//ERRNO
		//DOES NOT PRINT KEY WITHOUT VALUES
	}
	return (0);
}