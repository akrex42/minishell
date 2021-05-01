#include "minishell.h"

void 	ft_export(int argc, char **str, char **envp)
{
	char *equal;
	char *this_env;
	// char *key1;
	// char *key2;
	int i;
	char **beg_env;
	int flag_rep;

	flag_rep = 0;

	g_all.env = ft_allocate_env(envp); // we need to initialize it somewhere else
	i = 1;
	beg_env = g_all.env;
	// while (*g_all.env != 0 && i < argc)
	// {
	// 	this_env = *g_all.env;
	// 	// equal = ft_strchr(this_env, '=');
	// 	// if (equal == NULL)
	// 	// {
	// 	// 	i++;
	// 	// }
	// 	if (!(ft_strncmp(ft_substr(this_env, 0, ft_strlen(this_env) - ft_strlen(ft_strchr(this_env, '='))),
	// 					 ft_substr(str[i], 0, ft_strlen(str[i]) - ft_strlen(ft_strchr(str[i], '='))),
	// 					 ft_strlen(ft_substr(this_env, 0, ft_strlen(this_env) - ft_strlen(ft_strchr(this_env, '=')))))))
	// 	{
	// 		printf("%s\n", ft_substr(this_env, 0, ft_strlen(this_env) - ft_strlen(ft_strchr(this_env, '='))));
	// 		*g_all.env = ft_strdup(str[i]);
	// 		printf("%s\n", *g_all.env);
	// 		flag_rep = 1;
	// 		i++;
	// 		// g_all.env++;
	// 	}
	// 	// else
	// 	// {
	// 	// 	g_all.env = ft_allocate_env_builtins(g_all.env, 1, str[i], this_env);
	// 	// 	i++;
	// 	// 	// g_all.env++;
	// 	// 	// printf("%s\n", );
	// 	// }
	// 	g_all.env++;
	// }
	// g_all.flag_allocate = 0;
	// i = 0;
	// while ()
	while (*g_all.env != 0 && i < argc)
	{
		this_env = *g_all.env;
		equal = ft_strchr(str[i], '=');
		if (equal == NULL)
		{
			g_all.env = ft_allocate_env_builtins(g_all.env, 1, str[i], this_env);
		}
		else if (equal != NULL)
		{
			int j = 1;
			int k = 0;
			while (g_all.env[k] != NULL && j < argc)
			{
				this_env = g_all.env[k];
				if (!(ft_strncmp(ft_substr(g_all.env[k], 0, ft_strlen(g_all.env[k]) - ft_strlen(ft_strchr(g_all.env[k], '='))),
								ft_substr(str[j], 0, ft_strlen(str[j]) - ft_strlen(ft_strchr(str[j], '='))),
								ft_strlen(ft_substr(g_all.env[k], 0, ft_strlen(g_all.env[k]) - ft_strlen(ft_strchr(g_all.env[k], '=')))))))
				{
					printf("%s\n", ft_substr(g_all.env[k], 0, ft_strlen(g_all.env[k]) - ft_strlen(ft_strchr(this_env, '='))));
					g_all.env[k] = ft_strdup(str[j]);
					printf("%s\n", g_all.env[k]);
					// flag_rep = 1;
				}
				j++;
				k++;
			}
		}
		i++;
		g_all.env++;
	}
	// if (!(g_all.env = ft_allocate_env_builtins(g_all.env, 1, str[i], this_env)))
	// {
	// 	printf("%s", "error"); // error handling errors: g_all.env[0] != alpha, 
	// 	// error handling errors: g_all.env[0] != alpha,
	// 	// g_all.env[i] != isalphanum except for '=' and mb other bash reserved symbols
	// 	exit (-1);
	// 	// NEED TO ADD VALUES CHANGE HANDLING
// }
	int k = 0;
	// g_all.env = beg_env;
	while (g_all.env[k] != NULL)
	{
		this_env = g_all.env[k];
		equal = ft_strchr(this_env, '=');
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
		k++;
	}
}

int main (int argc, char **argv, char **envp)
{
	ft_export(argc, argv, envp);
	return (0);
}