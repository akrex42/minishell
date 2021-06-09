#include "minishell.h"

int	ft_cycle_unset(char **str, int i, char *equal)
{
	int		flag_return;
	int		j;
	char	**env2;

	flag_return = 0;
	j = 0;
	while (str[i] != NULL)
	{
		flag_return = print_err_unset(str[i]);
		if (flag_return)
		{
			i++;
			continue ;
		}
		env2 = g_all.env;
		j = 0;
		while (env2[j] != NULL)
			j = inner_circle3(j, i, str, equal);
		i++;
	}
	return (flag_return);
}
