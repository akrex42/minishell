#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft.h"


void 	ft_export(int argc, const char *str, char **envp)
{
//	int fd;
	if (argc == 1)
	{
		char **env = envp;
		while (*env != 0)
		{
			char *thisEnv = *env;
			printf("%s%s\n", "declare -x ", thisEnv); //NEED TO FIX "" issue - strdup??
			env++;
		}
	}
	else if (argc == 2)
	{
		char **env = envp;
		while (*env != 0)
		{
			env++;
		}
		*env = ft_strdup(str); //free
//		printf ("%s", *env);

		char **env1 = envp;
		while (*env1 != 0) //I ADDED IT JUST TO CHECK WHETHER I AM RIGHT
		{
			char *thisEnv = *env1;
			printf("%s%s\n", "declare -x ", thisEnv);
			env1++;
		}
	}
}
//	fd = open("dotenv", O_RDWR);
//	printf("%d", fd);

int main (int argc, char **argv, char **envp)
{
	if (argc == 1)
	{
		ft_export(argc, argv[0], envp);
	}
	else if (argc >= 2) //how to pass all the args?
	{
		ft_export(argc, argv[1], envp);
	}
	else
	{
		printf("%s", "error");
		return (-1);
	}
	return (0);
}