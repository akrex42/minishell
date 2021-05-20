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

void	ft_print_env(char *equal)
{
	char	**beg_env;

	beg_env = g_all.env;
	while (*g_all.env != NULL)
	{
		equal = ft_strchr(*g_all.env, '=');
		if (equal == NULL)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(*g_all.env, 1);
			ft_putchar_fd('\n', 1);
		}
		else
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(ft_substr(*g_all.env, 0, ft_strlen(*g_all.env) - ft_strlen(equal)), 1);
			ft_putchar_fd(equal[0], 1);
			ft_putchar_fd('"', 1);
			ft_putstr_fd(ft_substr(equal, 1, ft_strlen(equal) - 1), 1);
			ft_putchar_fd('"', 1);
			ft_putchar_fd('\n', 1);
		}
		g_all.env++;
	}
	g_all.env = beg_env;
}

int	ft_export(char **str)
{
	char	*equal;
	int		i;
	int		j;
	int		flag_equal;

	flag_equal = 0;
	// g_all.env = ft_allocate_env(envp); // we need to initialize it somewhere else
	i = 1; // Program name may be omitted with the use of exec* family
	if (str[i] == NULL)
		ft_print_env(equal);
	while (str[i] != NULL)
	{
		if (print_err_export_unset(str[i]))
			return (1);
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
	return (0);
}

/* int main (int argc, char **argv, char **envp)
// {
// 	ft_export(argv);
// 	return(0);
// } */
