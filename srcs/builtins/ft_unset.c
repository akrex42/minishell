#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft.h"


void 	ft_unset(const char *str, char **envp)
{
//	int fd;
	char *end;
	char *key;
	int len;
	char **env = envp;

	if (!(ft_isalpha(*str)))
	{
		printf("%s%s%s", "bash: unset: `", str, "': not a valid identifier\n");
		return ;
	}
	while (*env != 0)
	{
		char *thisEnv = *env;
		end = ft_strchr(thisEnv, '=');
		len = ft_strlen(end);
		key = ft_substr(thisEnv, 0, ft_strlen(thisEnv) - len); //free
		if (!(ft_strncmp(key, str, ft_strlen(str))))
		{
			//HOW TO DELETE THIS SHIT????
			thisEnv = "";
//			env--;
//			ft_strjoin(*env, thisEnv);
//			env++;
//			printf("%s\n", thisEnv);
//			thisEnv++;
//			env++;
		}
		printf("%s\n", thisEnv);
		env++;
	}
//	char **env1 = envp;
//	while (*env1 != 0) //I ADDED IT JUST TO CHECK WHETHER I AM RIGHT
//	{
//		char *thisEnv1 = *env1;
//		printf("%s%s\n", "declare -x ", thisEnv1);
//		env1++;
//	}
//	fd = open("dotenv", O_RDWR);
//	printf("%d", fd);
}

int main (int argc, char **argv, char **envp)
{
	if (argc > 1)
	{
		ft_unset(argv[1], envp);
	}
	return (0);
}