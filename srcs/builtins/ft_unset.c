#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft.h"

char	**ft_allocate_env(char **env);
void 	ft_unset(const char *str, char **envp)
{
//	int fd;
    char *end;
	char *key;
	int len;
	char **env = ft_allocate_env(envp);

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
		if (!(ft_strncmp(key, str, ft_strlen(key))))
		{
			//HOW TO DELETE THIS SHIT????
//			thisEnv = "";
			free(thisEnv);
			thisEnv = NULL;
//			printf("%s\n", "ff");
//			env--;
//			ft_strjoin(*env, thisEnv);
//			env++;
			printf("%s\n", thisEnv);
			break ;
//			thisEnv++;
		}
		env++;
	}
//	while (*env != 0)
//	{
//		char *thisEnv = *env;
//		*thisEnv = *(thisEnv + 1);
//	}
//	*thisEnv = NULL;
//	char **env1 = ft_allocate_env(env);
//	while (len1-- != 0)
//	{
//		char *thisEnv = env1[len1];
//		printf("%s\n", thisEnv);
//	}
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
