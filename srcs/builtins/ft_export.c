#include "minishell.h"

int	ft_check_equal(int i, int flag_equal, int j, char **str)
{
	if (ft_strlen(g_all.env[j])
		== ft_strlen(str[i]) && !(ft_strncmp(g_all.env[j],
				str[i], ft_strlen(str[i]))))
	{
		flag_equal = 1;
	}
	return (flag_equal);
}

int	ft_equal_null(char **str, int flag_equal, char *equal, int i)
{
	int		j;
	char	*key;

	j = 0;
	while (g_all.env[j] != NULL)
	{
		equal = ft_strchr(g_all.env[j], '=');
		if (equal == NULL)
			flag_equal = ft_check_equal(i, flag_equal, j, str);
		if (equal != NULL)
		{
			key = ft_substr(g_all.env[j], 0, ft_strlen(g_all.env[j])
					- ft_strlen(ft_strchr(g_all.env[j], '=')));
			flag_equal = ft_check_equal2(i, flag_equal, key, str);
		}
		j++;
	}
	return (flag_equal);
}

static void	ft_print_env(char *equal)
{
	int		i;
	char	*min;
	char	**env;
	int		j;
	int		change;

	i = 0;
	j = 0;
	min = NULL;
	change = 0;
	env = ft_allocate_env(g_all.env);
	while (env[i] != NULL)
	{
		ft_insertion_sort(env, min, change, i);
		i++;
	}
	ft_print_env_sorted(equal, env);
	i = 0;
	while (env[i] != NULL)
	{
		free(env[i]);
		i++;
	}
	free(env);
}

int	ft_export(char **str)
{
	char	*equal;
	int		i;
	int		j;
	int		flag_equal;
	int		flag_return;

	flag_equal = 0;
	flag_return = 0;
	i = 1;
	j = 0;
	equal = NULL;
	if (str[i] == NULL)
	{
		ft_print_env(equal);
		return (0);
	}
	flag_return = ft_cycle_export(str, i, equal, flag_equal);
	if (flag_return)
		return (1);
	return (0);
}
