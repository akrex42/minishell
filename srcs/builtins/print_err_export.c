#include "minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '	' || c == '\t' || c == '\v'
		|| c == '\f' || c == '\r' || c == '\n')
		return (1);
	return (0);
}

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
				&& (str[i] != '_') && (str[i] != '"')
				&& (str[i] != '\\') && (str[i] != '\'')
				&& (!ft_isspace(str[i])))
		{
			ft_putstr_fd("bash: export: `", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd("': not a valid identifier", 2);
			ft_putchar_fd('\n', 2);
			return (1);
		}
		if (str[i] == '"')
		{
			i++;
			while ((str[i] != '"') && (str[i] != '\0'))
			{
				i++;
			}
			//  ft_putstr_fd("here", 2);
		}
		i++;
	}
	return (0);
}
