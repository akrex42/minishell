#include "minishell.h"

int	ft_echo(char **str)
{
	int	flag;
	int	i;

	flag = 0;
	i = 1;
	// Parse key -n if needed
	if (str[1] != NULL && !(ft_strncmp(str[1], "-n", ft_strlen(str[1]))))
	{
		flag = 1;
		++i;
	}
	while (str[i] != NULL)
	{
		ft_putstr_fd(str[i], g_all.fd);
		ft_putchar_fd(' ', g_all.fd);
		i++;
	}
	if (str[1] != NULL)
		ft_putstr_fd(str[i], g_all.fd);
	if (!flag)
		ft_putchar_fd('\n', g_all.fd);
	return (0);
}

/* int main(int argc, char **argv)
// {
// 	ft_echo(argv);
// 	return(0);
// } */
