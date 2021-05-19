#include "minishell.h"

void 	ft_exit(char **argv) //implement errno here
{
	int i = 0;

	// atoi??
	while (argv[1] != '\0')
	{
		if (!ft_isalpha(argv[1][i]))
		{
			printf("%s%s%s", "bash: exit: ", argv[1], ": numeric argument required\n");
			return(1);
		}
		i++;
	}
	exit(error_code); // we should set this value to $?
}

int		main(int argc, char **argv, char **env)
{
	int errno;

	errno = 0; // perror?
	// EXIT FROM BASH, not builtins
	
	ft_exit(argv);
	return (0);
}