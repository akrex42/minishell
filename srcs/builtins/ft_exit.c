#include "minishell.h"

unsigned char 	ft_exit(char **str) //implement errno here
{
	int i;
	unsigned int error_code;

	i = 0;
	if (str[1] == NULL)
		return(0);
	while (str[1][i] != '\0')
	{
		if ((str[1][i] == '-' || str[1][i] == '+') && ft_isdigit(str[1][i + 1]))
			i++;
		else if (!ft_isdigit(str[1][i]))
		{
			ft_putstr_fd("bash: exit: ", 1);
			ft_putstr_fd(str[1], 1);
			ft_putstr_fd(": numeric argument required", 1);
			ft_putchar_fd('\n', 1);
			return(1);
		}
		i++;
	}
	error_code = (unsigned char)ft_atoi(str[1]);
	ft_putstr_fd("exit", 1);
	return(error_code); // we should set this value to $?
}

// int		main(int argc, char **argv, char **env)
// {
// 	// perror?
// 	// EXIT FROM BASH, not builtins
	
// 	ft_exit(argv);
// 	return(0);
// }