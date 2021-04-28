#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft.h"

void 	ft_exit(int error_code) //implement errno here
{
	exit(0);
}

int		main()
{
	int errno;
	
	ft_exit(errno);
	return (0);
}