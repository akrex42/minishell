#include "minishell.h"

int	print_err_exit(void)
{
	// ft_putstr_fd("exit\n", 1);
	ft_putstr_fd("my_bash: exit: too many arguments\n", 2);
	return (1);
}

void	ft_cycle_check_exit(char **str)
{
	int	i;

	i = 0;
	while (str[1][i] != '\0')
	{
		if ((str[1][i] == '-' || str[1][i] == '+') && ft_isdigit(str[1][i + 1]))
			i++;
		else if (!ft_isdigit(str[1][i]))
			ft_print_err_exit(str);
		i++;
	}
}

unsigned char   ft_exit(char **str)
{
	int				i;
	unsigned int	error_code;
	i = 0;
	error_code = 0;
	if (str == NULL)
	{
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
	else if (str[1] == NULL)
		g_all.exec.ret = check_cond();
	else if (str[1] != NULL)
	ft_cycle_check_exit(str);
	if (str[1] != NULL)
	{
		if (str[2] != NULL)
			return (print_err_exit());
		// ft_putstr_fd("exit\n", 1);
		error_code = (unsigned char)ft_atoi(str[1]);
	}
	exit(error_code);
}
