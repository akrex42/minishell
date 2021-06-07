#include "minishell.h"

static int	ft_isspace(char c)
{
	if (c == ' ' || c == '	' || c == '\t' || c == '\v'
		|| c == '\f' || c == '\r' || c == '\n')
		return (1);
	return (0);
}

int	ft_echo(char **str)
{
	int	flag;
	int	i;
	int j;

	flag = 0;
	i = 1;
	j = 0;

	if (str[1] == NULL)
	{
		ft_putchar_fd('\n', g_all.fd_out);
		return (0);
	}
	while (str[i] != NULL && !(ft_strncmp(str[i], "-n", 2)))
	{
		if (str[i][2] != '\0')
		{
			j = 2;
			while (str[i][j] != '\0')
			{
				if (str[i][j] != 'n')
				{
					ft_putstr_fd(str[i], g_all.fd_out);
					break ;
				}
				j++;
			}
			if (str[i][j] == '\0')
			{
				flag = 1;
			}
			i++;
		}
		else if (str[i][2] == '\0')
		{
			flag = 1;
			i++;
		}
		else
			break ;
	}
	while (str[i] != NULL && str[i + 1] != NULL)
	{
		j = 0;
		while (str[i][j] != '\0')
		{
			ft_putchar_fd(str[i][j], g_all.fd_out);
			j++;
		}
		ft_putchar_fd(' ', g_all.fd_out);
		i++;
	}
	ft_putstr_fd(str[i], g_all.fd_out);
	if (!flag)
		ft_putchar_fd('\n', g_all.fd_out);
	return (0);
}
