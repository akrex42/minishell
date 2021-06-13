#include "minishell.h"

int	ft_break(char **str, int i, int j)
{
	if (str[i][j] != 'n')
	{
		ft_putstr_fd(str[i], g_all.fd_out);
		ft_putchar_fd(' ', g_all.fd_out);
		return (1);
	}
	return (0);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '	' || c == '\t' || c == '\v'
		|| c == '\f' || c == '\r' || c == '\n')
		return (1);
	return (0);
}

int	ft_cycle_check_key(int j, char **str, int i)
{
	while (str[i] != NULL && !(ft_strncmp(str[i], "-n", 2)))
	{
		if (str[i][2] != '\0')
		{
			j = 2;
			while (str[i][j] != '\0')
			{
				if (ft_break(str, i, j))
					break ;
				j++;
			}
			if (str[i][j] == '\0')
				g_all.flag_echo = 1;
			i++;
		}
		else if (str[i][2] == '\0')
		{
			g_all.flag_echo = 1;
			i++;
		}
		else
			break ;
	}
	return (i);
}

void	ft_cycle_print_args(int i, char **str)
{
	int	j;

	j = 0;
	while (str[i] != NULL && str[i + 1] != NULL)
	{
		j = 0;
		while (ft_isspace(str[i][j]) == 1)
			j++;
		while (str[i][j] != '\0')
		{
			ft_putchar_fd(str[i][j], g_all.fd_out);
			j++;
		}
		ft_putchar_fd(' ', g_all.fd_out);
		i++;
	}
	ft_putstr_fd(str[i], g_all.fd_out);
	if (!g_all.flag_echo)
		ft_putchar_fd('\n', g_all.fd_out);
}

int	ft_echo(char **str)
{
	int	i;
	int	j;

	g_all.flag_echo = 0;
	i = 1;
	j = 0;
	if (str[1] == NULL)
	{
		ft_putchar_fd('\n', g_all.fd_out);
		return (0);
	}
	i = ft_cycle_check_key(j, str, i);
	ft_cycle_print_args(i, str);
	g_all.flag_echo = 0;
	return (0);
}
