#include "minishell.h"

static int	ft_isspace(char c)
{
	if (c == ' ' || c == '	' || c == '\t' || c == '\v'
		|| c == '\f' || c == '\r' || c == '\n')
		return (1);
	return (0);
}

int	ft_print_err_not_equal(char *str)
{
	char	*key;
	int		i;

	i = 0;
	key = ft_substr(str, 0, ft_strlen(str)
			- ft_strlen(ft_strchr(str, '=')));
	while (key[i] != '\0')
	{
		if (!ft_isalnum(key[i])
			&& (key[i] != '_') && (key[i] != '\\')
			&& (key[i] != '\'')
			&& (!ft_isspace(key[i])))
		{
			ft_putstr_fd("my_bash: export: `", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd("': not a valid identifier", 2);
			ft_putchar_fd('\n', 2);
			return (1);
		}
		i++;
	}
	free(key);
	return (0);
}

int	ft_print_err_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isalnum(str[i])
			&& (str[i] != '_') && (str[i] != '\\')
			&& (str[i] != '\''))
		{
			ft_putstr_fd("my_bash: export: `", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd("': not a valid identifier", 2);
			ft_putchar_fd('\n', 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int	print_err_export(char *str)
{
	int		i;

	i = 1;
	if (!ft_isalpha(str[0]) && (str[0] != '_'))
	{
		if (print(str))
			return (1);
	}
	if (str[0] == '\0')
	{
		if (print_1(str[0]))
			return (1);
	}
	if (!ft_strchr(str, '='))
	{
		if (ft_print_err_equal(str))
			return (1);
	}
	else
		if (ft_print_err_not_equal(str))
			return (1);
	return (0);
}
