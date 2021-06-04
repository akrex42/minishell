#include "minishell.h"

unsigned char 	ft_exit(char **str)
{
	int				i;
	unsigned int	error_code;

	i = 0;
	error_code = 0;
	if (str == NULL)
	{
		exit(0);
	}
	else if (g_all.commands->prev == NULL || (g_all.commands->prev->special[0] && g_all.commands->prev->special[0] != '|'))
	{
		ft_putstr_fd("exit\n", g_all.fd_out);
		ft_putchar_fd('\n', g_all.fd_out);
	}
	// ft_putstr_fd("here", g_all.fd_out);
	else if (str[0] != NULL && str[1] == NULL)
	{	
		if (g_all.commands->prev != NULL && (g_all.commands->prev->special[0] && g_all.commands->prev->special[0] == '|'))
			return (g_all.exec.ret);
		exit(g_all.exec.ret); // cause we need the last command exit status
	}
	else if (str[1] != NULL) // WTF???
	{
		while (str[1][i] != '\0')
		{
			if ((str[1][i] == '-' || str[1][i] == '+') && ft_isdigit(str[1][i + 1]))
				i++;
			else if (!ft_isdigit(str[1][i]))
			{
				ft_putstr_fd("bash: exit: ", 2);
				ft_putstr_fd(str[1], 2);
				ft_putstr_fd(": numeric argument required", 2);
				ft_putchar_fd('\n', 2);
				exit (255);
			}
			i++;
		}
	}

	// sleep(1000);
	if (str[1] != NULL)
	{
		error_code = (unsigned char)ft_atoi(str[1]); // returns 255 if error_code is out of range (0...255)
	}
	exit(error_code); // we should set this value to $?
}

// int		main(int argc, char **argv, char **env)
// {
// 	// perror?
// 	// EXIT FROM BASH, not builtins	
// 	ft_exit(argv);
// 	return(0);
// }
