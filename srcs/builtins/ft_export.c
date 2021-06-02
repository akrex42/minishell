#include "../includes/minishell.h"

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
	char	*key1;

	i = 0;
	while (g_all.env[i] != NULL)
	{
		equal = ft_strchr(g_all.env[i], '=');
		if (equal == NULL)
		{
			ft_putstr_fd("declare -x ", g_all.fd_out);
			ft_putstr_fd(g_all.env[i], g_all.fd_out);
			ft_putchar_fd('\n', g_all.fd_out);
		}
		else
		{
			ft_putstr_fd("declare -x ", g_all.fd_out);
			key = ft_substr(g_all.env[i], 0, ft_strlen(g_all.env[i]) - ft_strlen(equal));
			ft_putstr_fd(key, g_all.fd_out);
			free(key);
			ft_putchar_fd(equal[0], g_all.fd_out);
			ft_putchar_fd('"', g_all.fd_out);
			key1 = ft_substr(equal, 1, ft_strlen(equal) - 1);
			ft_putstr_fd(key1, g_all.fd_out);
			free(key1);
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
	i = 1; // Program name may be omitted with the use of exec* family
	if (str[i] == NULL)
	{
		ft_print_env(equal);
		return (0);
	}
	while (str[i] != NULL)
	{
		flag_return = print_err_export(str[i]);
		// if (flag_return)
		// {
		// 	i++;
		// 	continue ;
		// }
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

/* int main (int argc, char **argv, char **envp)
// {
// 	ft_export(argv);
// 	return(0);
// } */
