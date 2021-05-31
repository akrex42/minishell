#include "minishell.h"

int	ft_echo(char **str)
{
	int	flag;
	int	i;

	flag = 0;
	i = 1;
	// Parse key -n if needed
	// ft_putstr_fd(str[1], 1);
	// ft_putnbr_fd(g_all.flags.double_quote, 1);
	// ft_putchar_fd('\n', 1);
	// if (str[1] != NULL && !(ft_strncmp(str[1], "-n", ft_strlen(str[1]))))
	// {
	// 	flag = 1;
	// 	++i;
	// }
	while (g_all.flags.env--)
		ft_putchar_fd(' ', g_all.fd_out);
	while (!(ft_strncmp(str[i], "-n", 2)))
	{
		flag = 1;
		i++;
	}
	while (str[i + 1] != NULL)
	{
		ft_putstr_fd(str[i], g_all.fd_out);
		ft_putchar_fd(' ', g_all.fd_out);
		i++;
	}
	// if (str[1] != NULL)
	ft_putstr_fd(str[i], g_all.fd_out);
	if (!flag)
		ft_putchar_fd('\n', g_all.fd_out);
	return (0);
}

/* int main(int argc, char **argv)
// {
// 	ft_echo(argv);
// 	return(0);
// } */
