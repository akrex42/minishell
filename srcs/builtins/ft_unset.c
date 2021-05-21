#include "minishell.h"

int	print_err_unset(char *str)
{
	int	i;

	i = 1;
	if (str[1] == '\0' && !ft_isalpha(str[0]))
	{
		ft_putstr_fd("bash: unset: `", 1);
		ft_putstr_fd(str, 1);
		ft_putstr_fd("': not a valid identifier", 1);
		ft_putchar_fd('\n', 1);
		return (1); // errno?
	}
	while (str[i] != '\0')
	{
		if (!ft_isalnum(str[i]))
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
	char	**env1;
	int		k;

	g_all.flag_allocate = 0;
	i = 1;
	while (str[i] != NULL)
	{
		if (print_err_unset(str[i]) == 1)
			return (1);
		j = 0;
		while (g_all.env[j] != NULL)
		{
			char *equal = ft_strchr(g_all.env[j], '=');
			if (equal == NULL)
			{
				if (!(ft_strncmp(g_all.env[j], str[i], ft_strlen(str[i]))))
				{
					// ft_putstr_fd(g_all.env[j], 1);
					g_all.flag_allocate = 1;
					env1 = g_all.env;
					g_all.env = ft_allocate_env_builtins(1, str[i], g_all.env[j]);
					// ft_putstr_fd(g_all.env[0], 1);
					k = 0;
					while (env1[k] != NULL)
					{
						free(env1[k]);
						k++;
					}
					free(env1);
				}
			}
			else
			{
				key = ft_substr(g_all.env[j], 0, ft_strlen(g_all.env[j])
						- ft_strlen(equal));
				// ft_putstr_fd(g_all.env[j], 1);
				// ft_putchar_fd('\n', 1);
				// ft_putstr_fd(key, 1);
				if (!(ft_strncmp(key, str[i], ft_strlen(str[i]))))
				{
					// ft_putstr_fd(key, 1);
					g_all.flag_allocate = 1;
					env1 = g_all.env;
					g_all.env = ft_allocate_env_builtins(1, str[i], g_all.env[j]);
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
			j++;
		}
		i++;
	}
	g_all.flag_allocate = 0;
	return (0);
}

/* int main (int argc, char **argv, char **envp)
// {
// 	ft_unset(argv);
// 	return (0);
// } */
