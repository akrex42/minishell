#include "minishell.h"

// перевыделяет память для переменных окружения
char	**ft_allocate_env1(char **env)
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
	char *Thisret = *ret;
	while (i < len && *env1 != NULL)
	{
		char *thisEnv = *env1;
		equal = ft_strchr(thisEnv, '=');
		Thisret = ft_substr(thisEnv, 0, ft_strlen(thisEnv) - ft_strlen(equal) + 1);
		Thisret[ft_strlen(thisEnv) - ft_strlen(equal) + 1] = '"'; // we need to free it somewhere
		while (equal[j + 1] != '\0')
		{
			Thisret[ft_strlen(thisEnv) - ft_strlen(equal) + 2 + j] = equal[j];
			j++;
		}
		Thisret[ft_strlen(thisEnv) - ft_strlen(equal) + 2 + j + 1] = '"';
		Thisret[ft_strlen(thisEnv) - ft_strlen(equal) + 2 + j + 2] = '\0';
		i++;
		printf("%s\n", Thisret);
		env1++;
		ret++;
	}
	*ret = NULL;
	return (ret);
}