#include "minishell.h"

void	ft_make_pipes(void)
{
	int	i;

	i = ft_count_progs();
	g_all.pipes = malloc(sizeof(int *) * (i + 2));
	g_all.pipes[i + 1] = NULL;
	while (i >= 0)
	{
		g_all.pipes[i] = malloc(sizeof(int) * 2);
		pipe(g_all.pipes[i]);
		i--;
	}
}

void	ft_make_pid(void)
{
	int	i;

	i = ft_count_progs();
	g_all.pid = malloc(sizeof(int *) * (i + 1));
	g_all.pid[i] = NULL;
	i--;
	while (i >= 0)
	{
		g_all.pid[i] = malloc(sizeof(int) * 1);
		g_all.pid[i][0] = -1;
		i--;
	}
}

void	ft_free_pid(void)
{
	int	i;

	i = 0;
	while (g_all.pid[i])
	{
		free(g_all.pid[i]);
		i++;
	}
	free(g_all.pid[i]);
	free(g_all.pid);
}

void	ft_free_pipes(void)
{
	int	i;

	i = 0;
	while (g_all.pipes[i])
	{
		free(g_all.pipes[i]);
		i++;
	}
	free(g_all.pipes[i]);
	free(g_all.pipes);
}

void	ft_skip_redirect(void)
{
	while ((g_all.commands->used == 1
			|| (g_all.commands->special[0] == '|'
				&& g_all.commands->prog == NULL))
		&& g_all.commands->next)
		g_all.commands = g_all.commands->next;
}
