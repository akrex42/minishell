#include "minishell.h"

// перевыделяет память для переменных окружения // we need to free all of this
char	**ft_allocate_env_builtins(char **env, int args, char *str, char *this_env)
{
	char	**ret;
	int		len;
	int		i;

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
				ret[i] = ft_strdup(env[i + 1]); // we need to free it 
				i++;
			}
		}
		else
		{
			ret[i] = ft_strdup(env[i]); // we need to free it somewhere, memory per line
			i++;
		}
	}
	if (!g_all.flag_allocate)
	{
		ret[i] = ft_strdup(env[i]); // we need to free it somewhere, memory per line
		i++;
		ret[i] = ft_strdup(str);
		i++;
		ret[i] = NULL;
	}
	else
		ret[i] = NULL;
	return(ret);
}