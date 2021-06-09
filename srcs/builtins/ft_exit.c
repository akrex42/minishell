#include "minishell.h"

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

int	ft_check(int i, char **str)
{
	if (g_all.commands->prev != NULL
		&& (g_all.commands->prev->special[0]
			&& g_all.commands->prev->special[0] == '|'))
	{
		i = 0;
		while (str[1][i] != '\0')
		{
			if ((str[1][i] == '-' || str[1][i] == '+')
				&& ft_isdigit(str[1][i + 1]))
				i++;
			else if (!ft_isdigit(str[1][i]))
				return (ft_print_err_exit_return(str));
			i++;
		}
		return (g_all.exec.ret);
	}
	else
		ft_cycle_check_exit(str);
	return (0);
}

unsigned char 	ft_exit(char **str)
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
		if (ft_check(i, str))
			return (ft_check(i, str));
	if (str[1] != NULL)
		error_code = (unsigned char)ft_atoi(str[1]);
	exit(error_code);
}
