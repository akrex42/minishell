#include "minishell.h"

int	flag_zero(char **str, int flag_equal, int i)
{
	char	**env1;
	char	*this_env;
	int		k;

	if (flag_equal == 0)
	{
		env1 = g_all.env;
		g_all.env = ft_allocate_env_builtins(g_all.env, 1,
				str[i], this_env);
		k = 0;
		while (env1[k] != NULL)
		{
			free(env1[k]);
			k++;
		}
		free(env1);
	}		
	flag_equal = 0;
	return (flag_equal);
}

int	ft_key_value2(char **str, int i, int j, int flag_equal)
{
	char	*key;
	char	*this_env;
	char	*key1;

	key = ft_substr(g_all.env[j], 0, ft_strlen(g_all.env[j])
			- ft_strlen(ft_strchr(g_all.env[j], '=')));
	key1 = ft_substr(str[i], 0, ft_strlen(str[i])
			- ft_strlen(ft_strchr(str[i], '=')));
	if (ft_strlen(key) == ft_strlen(key1)
		&& ft_strncmp(key, key1, ft_strlen(key1)) == 0)
	{
		this_env = g_all.env[j];
		g_all.env[j] = ft_strdup(str[i]);
		free(this_env);
		flag_equal = 1;
		free(key);
		free(key1);
	}
	else
	{
		free(key);
		free(key1);
	}
	return (flag_equal);
}

int	ft_key_value1(char **str, int i, int j, int flag_equal)
{
	char	*key;
	char	*this_env;

	key = ft_substr(str[i], 0, ft_strlen(str[i])
			- ft_strlen(ft_strchr(str[i], '=')));
	if (ft_strlen(g_all.env[j]) == ft_strlen(key)
		&& !(ft_strncmp(g_all.env[j], key, ft_strlen(key))))
	{
		this_env = g_all.env[j];
		g_all.env[j] = ft_strdup(str[i]);
		free(this_env);
		flag_equal = 1;
		free(key);
	}
	else
		free(key);
	return (flag_equal);
}

int	internal_circle(int flag_equal, char **str, int i)
{
	int		j;
	char	*equal;

	j = 0;
	while (g_all.env[j] != NULL)
	{
		equal = ft_strchr(g_all.env[j], '=');
		if (equal == NULL)
		{					
			flag_equal = ft_key_value1(str, i, j, flag_equal);
			if (flag_equal == 1)
				break ;
		}
		if (equal != NULL)
		{
			flag_equal = ft_key_value2(str, i, j, flag_equal);
			if (flag_equal == 1)
				break ;
		}
		j++;
	}
	flag_equal = flag_zero(str, flag_equal, i);
	return (flag_equal);
}

int	ft_check_equal2(int i, int flag_equal, char *key, char **str)
{
	if (ft_strlen(key) == ft_strlen(str[i]) && !(ft_strncmp(key,
				str[i], ft_strlen(str[i]))))
	{
		flag_equal = 1;
		free(key);
		return (flag_equal);
	}
	else
		free(key);
	return (flag_equal);
}
