#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libft.h"
#include <errno.h> //errno

/* WE DON'T NEED TO USE FORK AS ALL THE PROCESSES ARE EXECUTED BY THE PARENT*/

void 	ft_cd(const char *str)
{
	char dir[1000];
	char *newdir;
	if ((strcmp(str, "-"))) //DO WE NEED TO MAKE TILDA?????
	{
		printf("Current directory is %s\n", getcwd(dir, 1000));
		printf("%d\n", chdir(str)); //we get the env variable home and change dir to there
		printf("Current directory is %s\n", getcwd(dir, 1000));
	}
	else
	{
		printf("Current directory is %s\n", getcwd(dir, 1000));
		printf("%d\n", chdir(getenv("OLDPWD"))); //we get the env variable oldpwd and change dir to there
		printf("Current directory is %s\n", getcwd(dir, 1000));
	}

	//WE NEED TO WRITE A NEW VALUE TO THE KEY PWD AND OLDPWD!!!!
	
	// else
	// {
	// 	// if
	// 	// {
	// 	// 	getcwd(dir, 1000);
	// 	// 	newdir = ft_strjoin(dir, "/");
	// 	// 	newdir = ft_strjoin(newdir, str);
	// 	// 	if (chdir(newdir) == -1)
	// 	// 	{
	// 	// 		printf("%s", "error\n");
	// 	// 		return ;
	// 	// 	}
	// 	// 	printf("%d\n", chdir(newdir)); // if -1 then print error
	// 	// 	printf("Current directory is %s\n", newdir);
	// 	// }
	// }
}

int 	main(int argc, char **argv)
{
	if (argc >= 2)
	{
		ft_cd(argv[1]);
	}
	else if (argc == 1)
	{
		char dir[1000];
		printf("%d\n", chdir(getenv("HOME"))); //we get the env variable home and change dir to there
		getcwd(dir, 1000); //add realloc and errors
		printf("Current directory is %s", dir);
		// ft_cd(argv[0]);
	}
	return (0);
}