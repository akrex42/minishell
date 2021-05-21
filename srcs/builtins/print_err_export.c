#include "minishell.h"

int	print_err_export(char *str)
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
