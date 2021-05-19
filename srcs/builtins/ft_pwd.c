#include "minishell.h"

int	ft_pwd(char **str)
{
	char dir[1000]; //WE WILL PARSE THIS SO IT WILL BE ALLOCATED DYNAMICALLY
	getcwd(dir, 1000); //add realloc and errors
	ft_putstr_fd(dir, 1);
	return(0);
}

// int main(int argc, char **argv, char **env)
// {
// 	ft_pwd(argc);
// }