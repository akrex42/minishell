#include "minishell.h"

void 	ft_export(int argc, char **str, char **envp)
{
	char *equal;
	char *this_env;
	// char *key1;
	// char *key2;
	int i;
	int j;
	int k;
	char **beg_env;
	int flag_rep;
	int flag_equal = 0;

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
	while (i < argc)
	{
		equal = ft_strchr(str[i], '=');
		if (equal != NULL && flag_rep == 0)
		{
			j = 1;
			k = 0; 
			while ((g_all.env[k] != NULL) && (j < argc))
			{
				this_env = g_all.env[k];
				equal = ft_strchr(str[j], '=');
				if (equal == NULL)
				{
					j++;
				}
				else if (!(ft_strncmp(ft_substr(g_all.env[k], 0, ft_strlen(g_all.env[k]) - ft_strlen(ft_strchr(g_all.env[k], '='))),
								ft_substr(str[j], 0, ft_strlen(str[j]) - ft_strlen(ft_strchr(str[j], '='))),
								ft_strlen(ft_substr(g_all.env[k], 0, ft_strlen(g_all.env[k]) - ft_strlen(ft_strchr(g_all.env[k], '=')))))))
				{
					// printf("%s\n", ft_substr(g_all.env[k], 0, ft_strlen(g_all.env[k]) - ft_strlen(ft_strchr(g_all.env[k], '='))));
					g_all.env[k] = ft_strdup(str[j]);
					// printf("%s\n", g_all.env[k]);
					flag_rep = 1;
					j++;
					k = 0;
				}
				// else if (!(ft_strncmp(ft_substr(g_all.env[k], 0, ft_strlen(g_all.env[k]) - ft_strlen(ft_strchr(g_all.env[k], '='))),
				// 				ft_substr(str[j], 0, ft_strlen(str[j]) - ft_strlen(ft_strchr(str[j], '='))),
				// 				ft_strlen(ft_substr(g_all.env[k], 0, ft_strlen(g_all.env[k]) - ft_strlen(ft_strchr(g_all.env[k], '=')))))))
				// {
					
				// }
				// printf("%s\n", g_all.env[k]);
				k++;
			}
		}
		else if (equal == NULL)
		{
			// printf("%s", "yes");
			k = 0;
			while (g_all.env[k] != NULL) // if key has no value??
			{
				equal = ft_strchr(g_all.env[k], '=');
				if (equal != NULL)
				{
					// printf("%s", "no");
					if (!(ft_strncmp(ft_substr(g_all.env[k], 0, ft_strlen(g_all.env[k]) - ft_strlen(ft_strchr(g_all.env[k], '='))),
							str[i], ft_strlen(ft_substr(g_all.env[k], 0, ft_strlen(g_all.env[k]) - ft_strlen(ft_strchr(g_all.env[k], '=')))))))
					{
						// printf("%s\n", g_all.env[k]);
						flag_equal = 1;
						// g_all.env[k] = ft_strdup(str[j]);
						// i++;
						break ;
					}
				// printf("%s\n", g_all.env[k]);
					k++;
				}
				else if (equal == NULL)
				{
					break ;
				}
			}
			// printf("%s", "oui");
			// printf("%s\n", g_all.env[k]);
			// printf("%s\n", str[i]);
			if (flag_equal == 0)
			{
				// printf("%s\n", g_all.env[k]);
				// *g_all.env = g_all.env[0];
				// printf("%s\n", str[i]);
				g_all.env = ft_allocate_env_builtins(g_all.env, 1, str[i], this_env);
			}
			// printf("%s\n", *g_all.env);
			flag_equal = 0;
			// i++;
			// printf("%s\n", *g_all.env);
		}
		else if (equal != NULL) // I need to add existing key WITHOUT value case
		{
			k = 0;
			while (g_all.env[k] != NULL)
			{
				if (!(ft_strncmp(g_all.env[k], str[i], ft_strlen(g_all.env[k]))))
				{
					// printf("%s\n", g_all.env[k]);
					flag_equal = 1;
					// i++;
					break ;
				}
				k++;
			}
			j = i;
			k = 0; 
			while ((g_all.env[k] != NULL))
			{
				equal = ft_strchr(str[j], '=');
				char *equal1 = ft_strchr(g_all.env[k], '=');
				if (equal1 == NULL)
				{
					if (!(ft_strncmp(g_all.env[k],
									ft_substr(str[j], 0, ft_strlen(str[j]) - ft_strlen(ft_strchr(str[j], '='))),
									ft_strlen(g_all.env[k]))))
					{
						// printf("%s\n", ft_substr(g_all.env[k], 0, ft_strlen(g_all.env[k]) - ft_strlen(ft_strchr(g_all.env[k], '='))));
						// printf("%s\n", g_all.env[k]);
						g_all.env[k] = ft_strdup(str[j]);
						// printf("%s\n", g_all.env[k]);
						// flag_rep = 1;
						break ;
					}
				}
				// else if (equal1 != NULL)
				// {
				// 	break ;
				// }
				// else if (!(ft_strncmp(ft_substr(g_all.env[k], 0, ft_strlen(g_all.env[k]) - ft_strlen(ft_strchr(g_all.env[k], '='))),
				// 				ft_substr(str[j], 0, ft_strlen(str[j]) - ft_strlen(ft_strchr(str[j], '='))),
				// 				ft_strlen(ft_substr(g_all.env[k], 0, ft_strlen(g_all.env[k]) - ft_strlen(ft_strchr(g_all.env[k], '=')))))))
				// {
					
				// }
				// printf("%s\n", g_all.env[k]);
				k++;
			}
			j = i;
			k = 0; 
			while (g_all.env[k] != NULL)
			{
				equal = ft_strchr(str[j], '=');
				char *equal1 = ft_strchr(g_all.env[k], '=');
				if (equal1 != NULL)
				{
					if (!(ft_strncmp(ft_substr(g_all.env[k], 0, ft_strlen(g_all.env[k]) - ft_strlen(ft_strchr(g_all.env[k], '='))),
									ft_substr(str[j], 0, ft_strlen(str[j]) - ft_strlen(ft_strchr(str[j], '='))),
									ft_strlen(ft_substr(g_all.env[k], 0, ft_strlen(g_all.env[k]) - ft_strlen(ft_strchr(g_all.env[k], '=')))))))
					{
						// printf("%s\n", ft_substr(g_all.env[k], 0, ft_strlen(g_all.env[k]) - ft_strlen(ft_strchr(g_all.env[k], '='))));
						// printf("%s\n", g_all.env[k]);
						g_all.env[k] = ft_strdup(str[j]);
						// flag_rep = 1;
						break ;
					}
				}
				else if (equal1 == NULL)
				{
					break ;
				}
			// 	// else if (!(ft_strncmp(ft_substr(g_all.env[k], 0, ft_strlen(g_all.env[k]) - ft_strlen(ft_strchr(g_all.env[k], '='))),
			// 	// 				ft_substr(str[j], 0, ft_strlen(str[j]) - ft_strlen(ft_strchr(str[j], '='))),
			// 	// 				ft_strlen(ft_substr(g_all.env[k], 0, ft_strlen(g_all.env[k]) - ft_strlen(ft_strchr(g_all.env[k], '=')))))))
			// 	// {
					
			// 	// }
			// 	// printf("%s\n", g_all.env[k]);
				k++;
			}
			if (flag_equal == 0)
			{
				// *g_all.env = g_all.env[0];
				g_all.env = ft_allocate_env_builtins(g_all.env, 1, str[i], this_env);
				// printf("%s\n", *g_all.env);
			}
			// printf("%s\n", *g_all.env);
			flag_equal = 0;
		}
		// else if (equal != NULL && flag_equal == 0)
		// {
		// 	j = 1;
		// 	k = 0; 
		// 	while ((g_all.env[k] != NULL) && (j < argc))
		// 	{
		// 		this_env = g_all.env[k];
		// 		equal = ft_strchr(str[j], '=');
		// 		if (equal == NULL)
		// 		{
		// 			j++;
		// 		}
		// 		else if (!(ft_strncmp(ft_substr(g_all.env[k], 0, ft_strlen(g_all.env[k]) - ft_strlen(ft_strchr(g_all.env[k], '='))),
		// 						ft_substr(str[j], 0, ft_strlen(str[j]) - ft_strlen(ft_strchr(str[j], '='))),
		// 						ft_strlen(ft_substr(g_all.env[k], 0, ft_strlen(g_all.env[k]) - ft_strlen(ft_strchr(g_all.env[k], '=')))))))
		// 		{
		// 			// printf("%s\n", ft_substr(g_all.env[k], 0, ft_strlen(g_all.env[k]) - ft_strlen(ft_strchr(g_all.env[k], '='))));
		// 			g_all.env[k] = ft_strdup(str[j]);
		// 			// printf("%s\n", g_all.env[k]);
		// 			flag_rep = 1;
		// 			j++;
		// 			k = 0;
		// 		}
		// 		// else if (!(ft_strncmp(ft_substr(g_all.env[k], 0, ft_strlen(g_all.env[k]) - ft_strlen(ft_strchr(g_all.env[k], '='))),
		// 		// 				ft_substr(str[j], 0, ft_strlen(str[j]) - ft_strlen(ft_strchr(str[j], '='))),
		// 		// 				ft_strlen(ft_substr(g_all.env[k], 0, ft_strlen(g_all.env[k]) - ft_strlen(ft_strchr(g_all.env[k], '=')))))))
		// 		// {
					
		// 		// }
		// 		// printf("%s\n", g_all.env[k]);
		// 		k++;
		// 	}
		// }
		// printf("%s\n", *g_all.env);
		i++;
		// printf("%s\n", str[i]);
	}
		// k = 0;
		// while ((g_all.env[k] != NULL) && (j < argc))
		// {
		// 	this_env = g_all.env[k];
		// 	equal = ft_strchr(str[j], '=');
		// 	if (!(ft_strncmp(ft_substr(g_all.env[k], 0, ft_strlen(g_all.env[k]) - ft_strlen(ft_strchr(g_all.env[k], '='))),
		// 						ft_substr(str[j], 0, ft_strlen(str[j]) - ft_strlen(ft_strchr(str[j], '='))),
		// 						ft_strlen(ft_substr(g_all.env[k], 0, ft_strlen(g_all.env[k]) - ft_strlen(ft_strchr(g_all.env[k], '=')))))))
		// 	{
		// 		k++;
		// 		j++;
		// 	}
		// 	else
		// 	{

		// 	}
		// 	printf("%s\n", g_all.env[k]);
		// 	k++;
		// }

	// if (!(g_all.env = ft_allocate_env_builtins(g_all.env, 1, str[i], this_env)))
	// {
	// 	printf("%s", "error"); // error handling errors: g_all.env[0] != alpha, 
	// 	// error handling errors: g_all.env[0] != alpha,
	// 	// g_all.env[i] != isalphanum except for '=' and mb other bash reserved symbols
	// 	exit (-1);
	// 	// NEED TO ADD VALUES CHANGE HANDLING
// }
	k = 0;
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