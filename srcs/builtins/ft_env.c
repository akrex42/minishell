#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft.h"


void 	ft_env(const char *str, char **envp)
{
//	int fd;
	char **env = envp;
	while (*env != 0)
	{
		char *thisEnv = *env;
		printf("%s\n", thisEnv);
		env++;
	}
}
//	fd = open("dotenv", O_RDWR);
//	printf("%d", fd);

int main (int argc, char **argv, char **envp)
{
	if (argc == 1)
	{
		ft_env(argv[0], envp);
	}
	else if (argc > 1)
	{
		printf("%s%s%s", "env: ", argv[1],": no such file or directory" );
		return (-1);
		//PERMISSION DENIED CASES AND WHEN $HOME -- WHAT SHALL WE DO?
	}
	return (0);
}