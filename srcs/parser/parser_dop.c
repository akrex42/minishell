#include "minishell.h"

// возвращает строку по названию переменной окружения
// ! не изменять строку
char	*ft_find_env_var(char *str)
{
	int	i;
	int	len;
	char	*equal;

	i = 0;
	len = ft_strlen(str);

	while (g_all.env[i] != NULL)
	{
		equal = ft_strchr(g_all.env[i], '=');
		if (equal == NULL) // key without value args cases
		{
			i++;
			continue ;
		}
		else
		{
			if (!ft_strncmp(g_all.env[i], str, len)
			&& g_all.env[i][len] == '=')
				return (&(g_all.env[i][len + 1]));
		}
		i++;
	}
	return (NULL);
}
