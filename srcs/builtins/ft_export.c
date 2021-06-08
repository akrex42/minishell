#include "minishell.h"

int	ft_check_equal(int i, int flag_equal, int j, char **str)
{
	if (ft_strlen(g_all.env[j])
		== ft_strlen(str[i]) && !(ft_strncmp(g_all.env[j],
				str[i], ft_strlen(str[i]))))
	{
		// if keys without values repeat and they do not have value in the list
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
	char	*key;
	char	*value;
	char 	*min;
	char	*tmp;
	char	*tmp1;

	int j = 0;
	i = 0;
	char **env = ft_allocate_env(g_all.env);
	while (env[i] != NULL)
	{
		j = i;
		min = env[j];
		int	change = j;

		while (env[j] != NULL)
		{
			equal = ft_strchr(env[j], '=');
			if (equal == NULL)
			{
				min = env[j];
				while (env[j] != NULL)
				{
					if (ft_strchr(env[j], '=') != NULL)
					{
						j++;
					}
					else if ((ft_strncmp(min, env[j], ft_strlen(min)) > 0))
					{
						min = env[j]; // how to recall it
						change = j;
					}
					else if ((ft_strncmp(min, env[j], ft_strlen(min)) == 0))
					{
						min = env[j]; // how to recall it
						change = j;
					}
					j++;
				}
			}
			else
			{
				if ((ft_strncmp(min, env[j], ft_strlen(min)) > 0))
				{
					min = env[j]; // how to recall it
					change = j;
				}
				else if ((ft_strncmp(min, env[j], ft_strlen(min)) == 0))
				{
					min = env[j]; // how to recall it
					change = j;
				}
				j++;
			}
		}
		tmp = env[i];
		env[i] = ft_strdup(min);
		tmp1 = env[change];
		env[change] = ft_strdup(tmp);
		free(tmp);
		free(tmp1);
		i++;
	}

	i = 0;
	while (env[i] != NULL)
	{
		equal = ft_strchr(env[i], '=');
		if (equal == NULL)
		{
			ft_putstr_fd("declare -x ", g_all.fd_out);
			ft_putstr_fd(env[i], g_all.fd_out);
			ft_putchar_fd('\n', g_all.fd_out);
		}
		else
		{
			ft_putstr_fd("declare -x ", g_all.fd_out);
			key = ft_substr(env[i], 0, ft_strlen(env[i]) - ft_strlen(equal));
			ft_putstr_fd(key, g_all.fd_out);
			free(key);
			ft_putchar_fd(equal[0], g_all.fd_out);
			ft_putchar_fd('"', g_all.fd_out);
			value = ft_substr(equal, 1, ft_strlen(equal) - 1);
			ft_putstr_fd(value, g_all.fd_out);
			free(value);
			ft_putchar_fd('"', g_all.fd_out);
			ft_putchar_fd('\n', g_all.fd_out);
		}
		i++;
	}	
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
	if (str[i] == NULL)
	{
		ft_print_env(equal);
		return (0);
	}
	while (str[i] != NULL)
	{
		flag_return = print_err_export(str[i]);
		if (flag_return)
		{
			i++;
			continue ;
		}
		equal = ft_strchr(str[i], '=');
		if (equal == NULL) // key without value args cases
		{
			flag_equal = ft_equal_null(str, flag_equal, equal, i);
			flag_equal = flag_zero(str, flag_equal, i);
		}
		else if (equal != NULL) // key with value args cases
			flag_equal = internal_circle(flag_equal, str, i);
		i++;
	}
	if (flag_return)
		return (1);
	return (0);
}
