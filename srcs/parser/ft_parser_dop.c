#include "minishell.h"

// возвращает перемалоченную строку по названию переменной окружения
char	*ft_find_env_var(char *str)
{
	int	i;
	int	len;
	// char	*tmp;

	i = 0;
	len = ft_strlen(str);
	while (g_all.env[i] != NULL)
	{
		if (!ft_strncmp(g_all.env[i], str, len)
			&& g_all.env[i][len] == '=')
		{
			return (&(g_all.env[i][len + 1]));
			// tmp = ft_strdup(&(g_all.env[i][len + 1]));
			// return (tmp);
		}
		i++;
	}
	return (NULL);
}