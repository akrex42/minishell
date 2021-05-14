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
	int l;
	char **beg_env;
	int flag_rep;
	int flag_equal = 0;

	flag_rep = 0;

	g_all.env = ft_allocate_env(envp); // we need to initialize it somewhere else
	i = 1;
	beg_env = g_all.env;

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
					g_all.env[k] = ft_strdup(str[j]);
					flag_rep = 1;
					j++;
					k = 0;
				}
				k++;
			}
		}
		else if (equal == NULL)
		{
			k = 0;
			while (g_all.env[k] != NULL) // if key has no value??
			{
				equal = ft_strchr(g_all.env[k], '=');
				if (equal != NULL)
				{
					if (!(ft_strncmp(ft_substr(g_all.env[k], 0, ft_strlen(g_all.env[k]) - ft_strlen(ft_strchr(g_all.env[k], '='))),
							str[i], ft_strlen(str[i]))))
					{
						// printf("%s\n", str[i]);
						flag_equal = 1;
						// break ;
					}
				}
				k++;
			}
			if (flag_equal == 0) // h h case breaks
			{
				k = 0;
				while (g_all.env[k] != NULL)
				{
					equal = ft_strchr(g_all.env[k], '=');
					if (equal != NULL)
					{
						if (ft_strncmp(ft_substr(g_all.env[k], 0, ft_strlen(g_all.env[k]) - ft_strlen(ft_strchr(g_all.env[k], '='))),
								str[i], ft_strlen(str[i])) == 0) //we need to compare the lenght of the arg, not the existing env
						{
							printf("%s\n", str[i]);
							flag_equal = 2;
							break ;
						}
					}
					k++;
				}
				if (flag_equal == 0)
				{
					// printf("%s\n", str[i]);
					g_all.env = ft_allocate_env_builtins(g_all.env, 1, str[i], this_env);
				}		
			}
			flag_equal = 0;
		}
		else if (equal != NULL) // I need to add existing key WITHOUT value case
		{
			k = 0;
			while (g_all.env[k] != NULL)
			{
				if (!(ft_strncmp(g_all.env[k], str[i], ft_strlen(g_all.env[k]))))
				{
					flag_equal = 1;
					break ;
				}
				k++;
			}
			if (flag_equal == 0)
			{
				k = 0; 
				while (g_all.env[k] != NULL)
				{
					equal = ft_strchr(g_all.env[k], '=');
					if (equal != NULL)
					{
						if (ft_strncmp(ft_substr(g_all.env[k], 0, ft_strlen(g_all.env[k]) - ft_strlen(ft_strchr(g_all.env[k], '='))),
								ft_substr(str[i], 0, ft_strlen(str[i]) - ft_strlen(ft_strchr(str[i], '='))),
								ft_strlen(ft_substr(str[i], 0, ft_strlen(str[i]) - ft_strlen(ft_strchr(str[i], '='))))) == 0)
						{
							flag_equal = 2;
							break ;
						}
					}
					k++;
				}
				if (flag_equal == 0)
				{
					// printf("%s\n", str[i]);
					g_all.env = ft_allocate_env_builtins(g_all.env, 1, str[i], this_env);
				}
			}
			flag_equal = 0;
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
						g_all.env[k] = ft_strdup(str[j]);
						break ;
					}
				}
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
									ft_strlen(ft_substr(str[j], 0, ft_strlen(str[j]) - ft_strlen(ft_strchr(str[j], '=')))))))
					{
						g_all.env[k] = ft_strdup(str[j]);
						break ;
					}
				}
				k++;
			}
		}
		i++;
	}
	k = 0;
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