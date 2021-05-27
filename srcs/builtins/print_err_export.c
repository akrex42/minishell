#include "minishell.h"

int	print_err_export(char *str)
{
	int	i;

	i = 1;
	if (!ft_isalpha(str[0]) && (str[0] != '_'))
	{
		ft_putstr_fd("bash: export: `", 2);
		ft_putchar_fd(str[0], 2);
		ft_putstr_fd("': not a valid identifier", 2);
		ft_putchar_fd('\n', 2);
		return (1); // errno?
	}
	while (str[i] != '\0')
	{
		if (!ft_isalnum(str[i]) && (str[i] != '=') 
				&& (str[i] != '_') && (str[i] != '"'))
		{
			ft_putstr_fd("bash: export: `", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd("': not a valid identifier", 2);
			ft_putchar_fd('\n', 2);
			return (1);
		}
		i++;
	}
	return (0);
}
