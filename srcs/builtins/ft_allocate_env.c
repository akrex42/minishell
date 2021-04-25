#include "minishell.h"

// перевыделяет память для переменных окружения
char	**ft_allocate_env(char **env)
{
	char	**ret;
	int		len;
	int		i;
	char 	*equal;
	char    **env1;
	char 	*key;
	int j;

	len = 0;
	j = 0;
	env1 = env;
	while (env[len] != NULL)
		len = len + 3;
	ret = malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (i < len && *env1 != NULL)
	{
		char *thisEnv = *env1;
		equal = ft_strchr(thisEnv, '=');
		ret[i] = ft_substr(thisEnv, 0, ft_strlen(thisEnv) - ft_strlen(equal));
		ret[i][j + ft_strlen(thisEnv) - ft_strlen(equal) - 1] = '"'; // we need to free it somewhere
		ret[i][j + ft_strlen(equal)] = *ft_strchr(thisEnv , '=');
		ret[i][j + ft_strlen(thisEnv) + 1] = '"'; 
		ret[i][j + ft_strlen(thisEnv) + 2] = '\0';
		i++;
		printf("%s", ret[i]);
		env1++;
	}
	ret[i] = NULL;
	return (ret);
}