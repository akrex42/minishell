#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft.h"


void 	ft_export(const char *str)
{
	int fd;
//	printf("%s\n", getenv("_"));
	fd = open("dotenv", O_RDWR);
	printf("%d", fd);
}

int main (int argc, char **argv)
{
	if (argc == 1)
	{
		ft_export(argv[0]);
	}
	return (0);
}