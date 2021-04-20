#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libft.h"
#include <errno.h> //errno

/* WE NEED TO USE FORK AND WAIT FOR THE PROCESS NOT TO FINISH */

//char *ft_strappend(char *str, char c)
//{
//	char *newstr;
//
//	newstr = malloc(ft_strlen(str) + 2);
//	while (str)
//	{
//		*newstr++ = *str++;
//	}
//	*newstr++ = c;
//	*newstr++ = '\0';
//	return (newstr);
//}
void 	ft_cd(const char *str)
{
	char dir[1000];
	char *newdir;
	if (!(strcmp(str, "/")))
	{
		printf("%d\n", chdir(getenv("HOME"))); //we get the env variable home and change dir to there
		getcwd(dir, 1000); //add realloc and errors
		printf("Current directory is %s", dir);
	}
	else if (!(strcmp(str, "..")))
	{
		getcwd(dir, 1000);
		char *last_slash;
		int len;
		last_slash = ft_strrchr(dir, '/');
		len = ft_strlen(last_slash);
		newdir = ft_substr(dir, 0, ft_strlen(dir) - len); //leak possible
		printf("%d\n", chdir(newdir)); //we ge the env old pwd (the previous directory where we was adn go there
//		getcwd(dir, 1000); //add realloc and errors
		printf("Current directory is %s\n", newdir);
//		printf("%d/n", len);
//		printf("%zu", ft_strlen(dir));
//		printf("%s", &last_slash[0]); //WORK WITH ../../ cases
	}
	else
	{
		if (str[0] == '/')
		{
			printf("%d\n", chdir(str));
			printf("Current directory is %s\n", str);
		}
		else if (str[0] == '.')
		{
			if (ft_strlen(str) > 1)
			{
				printf("%s%s%s", "cd:", str, ": No such file or directory"); //erno???
			}
		}
		else
		{
			getcwd(dir, 1000);
			newdir = ft_strjoin(dir, "/");
			newdir = ft_strjoin(newdir, str);
			printf("%d\n", chdir(newdir)); // if -1 then print error
			printf("Current directory is %s\n", newdir);
		}
	}
}

int 	main(int argc, char **argv)
{
	if (argc == 2)
	{
		ft_cd(argv[1]);
	}
	else if (argc == 1)
	{
		char dir[1000];
		printf("%d\n", chdir(getenv("HOME"))); //we get the env variable home and change dir to there
		getcwd(dir, 1000); //add realloc and errors
		printf("Current directory is %s", dir);
	}
	else
	{
		printf("%s", "too many arguments for cd");
	}
	return (0);
}