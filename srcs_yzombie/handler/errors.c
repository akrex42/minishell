#include "minishell.h"

void	ft_error_handler(int errno_exec)
{
	int	errno_pred;
	void	*dir;

	dir = NULL;
	if (errno_exec != 8 && errno_exec != 0 && errno_exec != 1)
	{
		ft_putstr_fd("my_bash: ", 1);
		ft_putstr_fd(g_all.comands->prog, 1);
		ft_putstr_fd(": ", 1);
		if (!ft_is_relative())
			ft_putstr_fd("command not found", 1);
		else if (errno_exec == 2 || errno_exec == 20)
			ft_putstr_fd(strerror(errno_exec), 1);
		else
		{
			dir = opendir(g_all.comands->prog);
			if (dir != NULL)
				ft_putstr_fd("is a directory", 1);
			else if (errno == 20 && errno_exec == 13)
				ft_putstr_fd(strerror(errno_pred), 1);
		}
		ft_putstr_fd("\n", 1); //  1) also permission denied when we did not chmod +x 2) no such file or directory
	}
	if (dir != NULL)
		closedir(dir);
}


// void	ft_error_handler(int ret)
// {
// 	int	errno_pred;
// 	void	*dir;

// 	dir = NULL;
// 	if (errno != 8)
// 	{
// 		errno_pred = errno;
// 		ft_putstr_fd("my_bash: ", 1);
// 		ft_putstr_fd(g_all.comands->prog, 1);
// 		ft_putstr_fd(": ", 1);
// 		if (ret == -1)
// 			ft_putstr_fd("command not found", 1);
// 		else if (errno == 2 || errno == 20)
// 			ft_putstr_fd(strerror(errno), 1);
// 		else
// 		{
// 			dir = opendir(g_all.comands->prog);
// 			if (errno == 13)
// 				ft_putstr_fd("is a directory", 1);
// 			else if (errno == 20 && errno_pred == 13)
// 				ft_putstr_fd(strerror(errno_pred), 1);
// 		}
// 		ft_putstr_fd("\n", 1);
// 	}
// 	if (dir != NULL)
// 		closedir(dir);
// }
