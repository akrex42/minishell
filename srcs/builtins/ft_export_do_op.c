#include "minishell.h"

void	ft_print_equal(char **env, int i, char *equal)
{
	char	*key;
	char	*value;

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

int	ft_insertion_sort(char **env, char *min, int change, int i)
{
	int	j;

	j = i;
	min = env[j];
	change = j;
	while (env[j] != NULL)
	{
		if ((ft_strncmp(min, env[j], ft_strlen(min)) > 0))
		{
			min = env[j];
			change = j;
		}
		else if ((ft_strncmp(min, env[j], ft_strlen(min)) == 0))
		{
			min = env[j];
			change = j;
		}
		j++;
	}
	ft_swap_and_free(min, change, env, i);
	return (change);
}

void	ft_print_env_sorted(char *equal, char **env)
{
	int		i;

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
			ft_print_equal(env, i, equal);
		i++;
	}
}

void	ft_swap_and_free(char *min, int change, char **env, int i)
{
	char	*tmp;
	char	*tmp1;

	tmp = env[i];
	env[i] = ft_strdup(min);
	tmp1 = env[change];
	env[change] = ft_strdup(tmp);
	free(tmp);
	free(tmp1);
}

int	ft_cycle_export(char **str, int i,
	char *equal, int flag_equal)
{
	int	flag_return;
	int	flag_one;

	flag_return = 0;
	flag_one = 0;
	while (str[i] != NULL)
	{
		flag_return = print_err_export(str[i]);
		if (flag_return)
		{
			i++;
			flag_one = 1;
			continue ;
		}
		equal = ft_strchr(str[i], '=');
		if (equal == NULL)
		{
			flag_equal = ft_equal_null(str, flag_equal, equal, i);
			flag_equal = flag_zero(str, flag_equal, i);
		}
		else if (equal != NULL)
			flag_equal = internal_circle(flag_equal, str, i);
		i++;
	}
	return (flag_one);
}
