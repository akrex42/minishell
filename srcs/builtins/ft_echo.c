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
	// Parse key -n if needed // may be an empty string
	if (str[1] == NULL)
	{
		ft_putchar_fd('\n', g_all.fd_out);
		return (0);
	}
	// FIXME
	while (!(ft_strncmp(str[i], "-n", 2)))
	{
		flag = 1;
		i++;
	}
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
	if (!flag)
		ft_putchar_fd('\n', g_all.fd_out);
	g_all.flags.env = 0;
	return (0);
}

/* int main(int argc, char **argv)
// {
// 	ft_echo(argv);
// 	return(0);
// } */
