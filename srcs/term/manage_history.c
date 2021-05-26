#include "minishell.h"

// 1 - алгоритм прошел, 0 - алгоритм не прошел 
int	ft_manage_history(t_term_all *all)
{
	if (!ft_strncmp(all->wr, "\e[A", 100) || !ft_strncmp(all->wr, "\e[B", 100))
	{
		g_all.curr_str = 2;
		free(all->str_hist);
		ft_malloc_one_char_str(&(all->str_hist));
		tputs(restore_cursor, 1, ft_putchar);
		tputs(clr_eos, 1, ft_putchar);
		if (!ft_strncmp(all->wr, "\e[A", 100))
			ft_history_step_back(&(all->history));
		else if (!ft_strncmp(all->wr, "\e[B", 100))
			ft_history_step_front(&(all->history));
		if (all->history->content != NULL)
			ft_putstr_fd(all->history->content, 1);
		else
		{
			g_all.curr_str = 1;
			ft_putstr_fd(all->str, 1);
		}
		return (1);
	}
	return (0);
}
