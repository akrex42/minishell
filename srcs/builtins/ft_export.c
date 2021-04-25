#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft.h"

char	**ft_allocate_env(char **env);
void 	ft_export(int argc, const char *str, char **envp)
{
//	int fd;
	char **envp1;
	envp1 = ft_allocate_env(envp);
	while (*envp1 != NULL)
	{
		char *thisEnv = *envp1;
		printf("%s\n", thisEnv);
		envp1++;
	}
// 	if (argc == 1)
// 	{
// 		while (*envp1 != 0)
// 		{
// 			char *thisEnv = *envp1;
// 			printf("%s%s\n", "declare -x ", thisEnv); //NEED TO FIX "" issue - strdup??
// 			envp1++;
// 		}
// 	}
// 	//I need to find all the keys and wrap them up into brackets
// 	else if (argc == 2)
// 	{
// 		char **env = envp;
// 		while (*env != 0)
// 		{
// 			env++;
// 		}
// 		*env = ft_strdup(str); //free
// //		printf ("%s", *env);

// 		char **env1 = envp;
// 		while (*env1 != 0) //I ADDED IT JUST TO CHECK WHETHER I AM RIGHT
// 		{
// 			char *thisEnv = *env1;
// 			printf("%s%s\n", "declare -x ", thisEnv);
// 			env1++;
// 		}
// 	}
}

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