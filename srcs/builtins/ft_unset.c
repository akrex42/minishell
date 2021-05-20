#include "minishell.h"

int	print_err_export_unset(char *str)
{
	int	i;

	i = 1;
	if (!ft_isalpha(str[0]))
	{
		ft_putstr_fd("bash: export: `", 1);
		ft_putchar_fd(str[0], 1);
		ft_putstr_fd("': not a valid identifier", 1);
		ft_putchar_fd('\n', 1);
		return (1); // errno?
	}
	while (str[i] != '\0')
	{
		if (!ft_isalnum(str[i]) && str[i] != '=')
		{
			ft_putstr_fd("bash: export: `", 1);
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
	char	**beg_e;
	int		i;

	i = 1;
	beg_e = g_all.env;
	while (*g_all.env != 0 && str[i] != NULL)
	{
		if (print_err_export_unset(str[i]) == 1)
			return (1);
		key = ft_substr(*g_all.env, 0, ft_strlen(*g_all.env)
				- ft_strlen(ft_strchr(*g_all.env, '=')));
		if (!(ft_strncmp(key, str[i], ft_strlen(str[i]))))
		{
			g_all.flag_allocate = 1;
			g_all.env = ft_allocate_env_builtins(beg_e, 1, str[i], *g_all.env);
			beg_e = g_all.env;
			i++;
		}
		else
			g_all.env++;
		free(key);
	}
	g_all.flag_allocate = 0;
	return (0);
}

/* int main (int argc, char **argv, char **envp)
// {
// 	ft_unset(argv);
// 	return (0);
// } */
