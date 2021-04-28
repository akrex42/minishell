#include "minishell.h"

// перевыделяет память для переменных окружения
char	**ft_allocate_env(char **env, int args, char **str, char *this_env)
{
	char	**ret;
	int		len;
	int		i;

	len = 0;
	while (env[len] != NULL)
		len++;
	if (g_all.flag_allocate == 1)
	{
		ret = malloc(sizeof(char *) * (len));
	}
	else
	{
		ret = malloc(sizeof(char *) * (len + args)); //for every pointer
	}
	i = 0;
	while (i < len)
	{
		if (g_all.flag_allocate == 1 && !(ft_strncmp(env[i], this_env, ft_strlen(this_env))))
		{
			while (i < len - 1)
			{
				ret[i] = ft_strdup(env[i + 1]); // we need to free it somewhere, memory per line
				i++;
			}
		}
		else
		{
			ret[i] = ft_strdup(env[i]); // we need to free it somewhere, memory per line
			i++;
		}
	}
	int j = 1;
	if (args > 1 && !g_all.flag_allocate)
	{
		while (j < args)
		{
			ret[i] = ft_strdup(str[j]);
			i++;
			j++;
		}
		ret[i] = NULL;
	}
	else
		ret[i] = NULL;
	return (ret);
}