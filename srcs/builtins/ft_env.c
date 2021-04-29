#include "minishell.h"

void 	ft_env(int argc, char **str, char **envp)
{
	char *equal;
	char *this_env;

	g_all.env = ft_allocate_env(envp);
	if (argc == 1)
	{
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
	else if (argc > 1)
	{
		print_err(-2); //-2 can be for ENV
		// printf("%s%s%s", "env: ", str[1],": No such file or directory\n" ); // ONLY ONE ERROR CAN OCCUR
		// return ;
	}
}

int main (int argc, char **argv, char **envp)
{
	ft_env(argc, argv, envp);
	return (0);
}