#include "minishell.h"

int		print_err(int errno)
{
	strerror(errno);
	exit(errno);
}