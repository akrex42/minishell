#include "minishell.h"

static int	ft_isspace(char c)
{
	if (c == ' ' || c == '	' || c == '\t' || c == '\v'
		|| c == '\f' || c == '\r' || c == '\n')
		return (1);
	return (0);
}

int	print_err_export(char *str)
{
	int	i;
	char *key;

	i = 1;
	if (!ft_isalpha(str[0]) && (str[0] != '_'))
	{
		ft_putstr_fd("my_bash: export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier", 2);
		ft_putchar_fd('\n', 2);
		return (1); // errno?
	}
	if (str[0] == '\0')
	{
		ft_putstr_fd("my_bash: export: `", 2);
		ft_putchar_fd(str[0], 2);
		ft_putstr_fd("': not a valid identifier", 2);
		ft_putchar_fd('\n', 2);
		return (1);
	}
	if (!ft_strchr(str, '='))
	{
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
	}
	else
	{
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
	}

	// while (str[i] != '\0')
	// {
	// 	if (str[i] != '\"')
	// 	{
	// 		if (!ft_isalnum(str[i]) && (str[i] != '=') 
	// 		&& (str[i] != '_')
	// 		&& (str[i] != '\\') && (str[i] != '\'')
	// 		&& (!ft_isspace(str[i])))
	// 		{
	// 			ft_putstr_fd("bash: export: `", 2);
	// 			ft_putstr_fd(str, 2);
	// 			ft_putstr_fd("': not a valid identifier", 2);
	// 			ft_putchar_fd('\n', 2);
	// 			return (1);
	// 		}
	// 	}
	// 	else if (str[i] == '\"')
	// 	{
	// 		i++;
	// 		while ((str[i] != '\"') && (str[i] != '\0'))
	// 		{
	// 			i++;
	// 		}
	// 		//  ft_putstr_fd("here", 2);
	// 	}
	// 	i++;
	// }
	return (0);
}
