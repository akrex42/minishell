#include "minishell.h"

// перевыделяет память для переменных окружения
char	**ft_allocate_env1(char **env)
{
	char	**ret;
	int		len;
	int		i;

	len = 0;
	while (env[len] != NULL)
		len++;
	ret = malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (i < len)
	{
		ret[i] = ft_strdup(env[i]); // we need to free it somewhere
		i++;
	}
	ret[i] = NULL;
	return (ret);
}