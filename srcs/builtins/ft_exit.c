#include "minishell.h"

void 	ft_exit(int error_code) //implement errno here
{
	exit(error_code); // we should set this value to $?
}

int		main()
{
	int errno;

	errno = 0; // perror?
	// EXIT FROM BASH, not builtinse
	
	ft_exit(errno);
	return (0);
}