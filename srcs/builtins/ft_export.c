#include "minishell.h"

void 	ft_export(int argc, char **str, char **envp)
{
	char *equal;
	char *key;
	char *this_env;
	int i;
	int j;
	int flag_equal;
	char **env1;

	flag_equal = 0;
	g_all.env = ft_allocate_env(envp); // we need to initialize it somewhere else
	i = 1; // Program name may be omitted with the use of exec* family

	while (i < argc)
	{
		equal = ft_strchr(str[i], '=');
		if (equal == NULL) // key without value args cases
		{
			j = 0;
			while (g_all.env[j] != NULL)
			{
				equal = ft_strchr(g_all.env[j], '=');
				if (equal == NULL)
				{
					if (ft_strlen(g_all.env[j]) 
						== ft_strlen(str[i]) && !(ft_strncmp(g_all.env[j],
							str[i], ft_strlen(str[i]))))
					{
						// printf("%s\n", str[i]); // if keys without values repeat and tey do not have value in the list
						flag_equal = 1;
						break ;
					}
				}
				if (equal != NULL)
				{
					key = ft_substr(g_all.env[j], 0, ft_strlen(g_all.env[j]) - ft_strlen(ft_strchr(g_all.env[j], '=')));
					if (ft_strlen(key) == ft_strlen(str[i]) && !(ft_strncmp(key,
							str[i], ft_strlen(str[i]))))
					{
						// printf("%s\n", str[i]); // if keys without values repeat and they have value assigned in the list
						flag_equal = 1;
						break ;
					}
					free(key);
				}
				j++;
			}
			if (flag_equal == 0)
			{
				// printf("%s\n", str[i]); // all the keys without value that do not repeat OR first time appeared repeating ones
				env1 = g_all.env;
				g_all.env = ft_allocate_env_builtins(g_all.env, 1, str[i], this_env);
				free(env1);
			}		
			flag_equal = 0;
		}
		else if (equal != NULL) // key with value args cases
		{
			j = 0;
			while (g_all.env[j] != NULL)
			{
				equal = ft_strchr(g_all.env[j], '=');
				if (equal == NULL)
				{
					key = ft_substr(str[i], 0, ft_strlen(str[i]) - ft_strlen(ft_strchr(str[i], '=')));
					if (ft_strlen(g_all.env[j]) == ft_strlen(key) 
							&& !(ft_strncmp(g_all.env[j], key,
							ft_strlen(key))))
					{
						// if we assign value to an existing key for the first time
						// printf("%s\n", g_all.env[k]);
						this_env = g_all.env[j];
						g_all.env[j] = ft_strdup(str[i]);
						free(this_env);
						// free
						// printf("%s\n", g_all.env[k]);
						flag_equal = 1;
						break ;
					}
					free(key);
				}
				if (equal != NULL)
				{
					key = ft_substr(g_all.env[j], 0, ft_strlen(g_all.env[j]) - ft_strlen(ft_strchr(g_all.env[j], '=')));
					char *key1 = ft_substr(str[i], 0, ft_strlen(str[i]) - ft_strlen(ft_strchr(str[i], '=')));
					if (ft_strlen(key) == ft_strlen(key1)
						&& ft_strncmp(key, key1, ft_strlen(key1)) == 0)
					{
						// printf("%s\n", str[i]); // if key-=value already exists in the list and we change it, including final variant
						// printf("%s\n", g_all.env[j]);
						this_env = g_all.env[j];
						g_all.env[j] = ft_strdup(str[i]);
						free(this_env);
						// printf("%s\n", g_all.env[j]);
						flag_equal = 1;
						break ;
					}
					free(key);
					free(key1);
				}
				j++;
			}
			if (flag_equal == 0)
			{
				// printf("%s\n", str[i]); // key=value included in the list for the first timie
				env1 = g_all.env;
				g_all.env = ft_allocate_env_builtins(g_all.env, 1, str[i], this_env);
				free(env1);
			}		
			flag_equal = 0;
		}
		i++;
	}


	j = 0;
	while (g_all.env[j] != NULL)
	{
		this_env = g_all.env[j];
		equal = ft_strchr(this_env, '=');
		if (equal == NULL)
		{
			printf("%s%s%c", "declare -x ", this_env, '\n');
		}
		else
		{
			printf("%s", "declare -x ");
			char *env = ft_substr(this_env, 0, ft_strlen(this_env) - ft_strlen(equal));
			printf("%s", env);
			free(env);
			printf("%c", equal[0]);
			printf("%c", '"');
			env = ft_substr(equal, 1, ft_strlen(equal) - 1);
			printf("%s", env);
			free(env);
			printf("%c%c", '"', '\n');
		}
		j++;
	}
	sleep (1000);
}

int main (int argc, char **argv, char **envp)
{
	ft_export(argc, argv, envp);
	return (0);
}