#include "minishell.h"

void	ft_commands_go_beginning(void)
{
	while (g_all.comands->prev != NULL)
		g_all.comands = g_all.comands->prev;
}