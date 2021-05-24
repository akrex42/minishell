#include "../includes/minishell.h"

void	inner_circle2(int j, int i, char **str, char *equal)
{
	char	*key;
	char	**env1;
	int		k;

	key = ft_substr(g_all.env[j], 0, ft_strlen(g_all.env[j])
			- ft_strlen(equal));
	if (ft_strlen(key)
		== ft_strlen(str[i]) && !(ft_strncmp(g_all.env[j], str[i],
				ft_strlen(str[i]))))
	{
		g_all.flag_allocate = 1;
		env1 = g_all.env;
		g_all.env = ft_allocate_env_builtins(g_all.env, 1, str[i],
				g_all.env[j]);
		k = 0;
		while (env1[k] != NULL)
		{
			free(env1[k]);
			k++;
		}
		free(env1);
	}
	free(key);
}

void	inner_circle(int j, int i, char **str)
{
	char	**env1;
	int		k;

	if (ft_strlen(g_all.env[j])
		== ft_strlen(str[i]) && !(ft_strncmp(g_all.env[j], str[i],
				ft_strlen(str[i]))))
	{
		g_all.flag_allocate = 1;
		env1 = g_all.env;
		g_all.env = ft_allocate_env_builtins(g_all.env, 1, str[i],
				g_all.env[j]);
		k = 0;
		while (env1[k] != NULL)
		{
			free(env1[k]);
			k++;
		}
		free(env1);
	}
}

int	inner_circle3(int j, int i, char **str, char *equal)
{
	if (g_all.env[j] != NULL)
	{
		equal = ft_strchr(g_all.env[j], '=');
		if (equal == NULL)
			inner_circle(j, i, str);
		if (equal != NULL)
			inner_circle2(j, i, str, equal);
	}
	j++;
	return (j);
}

int	print_err_unset(char *str)
{
	int	i;

	i = 1;
	if (!ft_isalpha(str[0]) && (str[0] != '_'))
	{
		ft_putstr_fd("bash: unset: `", 1);
		ft_putstr_fd(str, 1);
		ft_putstr_fd("': not a valid identifier", 1);
		ft_putchar_fd('\n', 1);
		return (1); // errno?
	}
	while (str[i] != '\0')
	{
		if ((!ft_isalnum(str[i])) || (str[i] != '_'))
		{
			ft_putstr_fd("bash: unset: `", 1);
			ft_putstr_fd(str, 1);
			ft_putstr_fd("': not a valid identifier", 1);
			ft_putchar_fd('\n', 1);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_unset(char **str)
{
	char	*key;
	int		i;
	int		j;
	char	**env2;
	char	*equal;

	g_all.flag_allocate = 0;
	i = 1;
	while (str[i] != NULL)
	{
		if (print_err_unset(str[i]) == 1)
			return (1);
		env2 = g_all.env;
		j = 0;
		while (env2[j] != NULL)
			j = inner_circle3(j, i, str, equal);
		i++;
	}
	g_all.flag_allocate = 0;
	return (0);
}
