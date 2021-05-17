#include "minishell.h"

// перевыделяет память для переменных окружения // we need to free all of this
char	**ft_allocate_env_builtins(char **env, int args, char *str, char *this_env)
{
	char	**ret;
	int		len;
	int		i;
	int		j;

	len = 0;
	while (env[len] != NULL)
		len++;
	if (g_all.flag_allocate == 1)
		ret = malloc(sizeof(char *) * (len));
	else
		ret = malloc(sizeof(char *) * (len + 2)); //for every pointer
	i = 0;
	while (i < len - 1)
	{
		if (g_all.flag_allocate == 1 && !(ft_strncmp(env[i], this_env, ft_strlen(this_env))))
		{
			while (i < len - 1)
			{
				ret[i] = ft_strdup(env[i + 1]); // we need to free it somewhere, memory per line
				// free(env[i + 1]);
				i++;
			}
		}
		else
		{
			ret[i] = ft_strdup(env[i]); // we need to free it somewhere, memory per line
			// free(env[i]);
			i++;
		}
	}
	j = 1;
	if (!g_all.flag_allocate)
	{
		ret[i] = ft_strdup(env[i]); // we need to free it somewhere, memory per line
		// free(env[i]);
		i++;
		ret[i] = ft_strdup(str);
		i++;
		ret[i] = NULL;
	}
	else
		ret[i] = NULL;
	// sleep (1000);
	// free(env);
	return(ret);
}

// int main(int argc, char **argv, char **env)
// {
// 	ft_allocate_env_builtins(env, argc, *argv, "str");
// 	return (0);
// }