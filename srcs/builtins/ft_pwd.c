#include "minishell.h"

void	ft_pwd(int argc)
{
	// if (argc == 1)
	// {
		char dir[1000]; //WE WILL PARSE THIS SO IT WILL BE ALLOCATED DYNAMICALLY
		getcwd(dir, 1000); //add realloc and errors
		printf("%s", dir);
	// }
	// else
	// {
	// 	print_error_pwd();
	// }
}

int main(int argc, char **argv, char **env)
{
	ft_pwd(argc);
}