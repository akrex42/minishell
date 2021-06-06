#include "minishell.h"

int	ft_is_relative(void)
{
	if (ft_strrchr(g_all.commands->prog, '/') != NULL)
		return (1);
	return (0);	
}

void	ft_sighnd_exec(int signo)
{
	if (signo == 3) // ctrl + '\'
	{
		ft_putstr_fd("Quit: 3\n", 1);
		g_all.exit_status = 501;
	}
	else
	{
		ft_putstr_fd("\n", 1);
		g_all.exit_status = 500; // используется как флаг для изменения этого значения после форка
	}
}

void	ft_rewrite_path(void)
{
	int	i;

	if (g_all.path != NULL)
	{
		i = 0;
		while (g_all.path[i] != NULL)
		{
			free(g_all.path[i]);
			i++;
		}
		free(g_all.path);
	}
	g_all.path = ft_split(ft_find_env_var("PATH"), ':');
}
