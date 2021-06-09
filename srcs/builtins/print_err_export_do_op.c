#include "minishell.h"

int 	print(char *str)
{
	ft_putstr_fd("my_bash: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier", 2);
	ft_putchar_fd('\n', 2);
	return (1);
}

int 	print_1(char str)
{
	ft_putstr_fd("my_bash: export: `", 2);
	ft_putchar_fd(str, 2);
	ft_putstr_fd("': not a valid identifier", 2);
	ft_putchar_fd('\n', 2);
	return (1);
}
