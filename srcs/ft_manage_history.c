#include "main_term.h"

// 1 - алгоритм прошел, 0 - алгоритм не прошел 
int	ft_manage_history(const char *wr, char **str,
		t_hystory_list **history)
{
	if (!ft_strncmp(wr, "\e[A", 100) || !ft_strncmp(wr, "\e[B", 100))
	{
		tputs(restore_cursor, 1, ft_putchar);
		tputs(clr_eos, 1, ft_putchar);
		if (!ft_strncmp(wr, "\e[A", 100))
		{
			ft_history_step_back(history);
			ft_putstr_fd((*history)->content, 1);
		}
		else if (!ft_strncmp(wr, "\e[B", 100))
		{ 
			ft_history_step_front(history);
			if ((*history)->content != NULL)
				ft_putstr_fd((*history)->content, 1);
			else
				ft_putstr_fd(*str, 1);
		}
		return (1);
	}
	return (0);
}
