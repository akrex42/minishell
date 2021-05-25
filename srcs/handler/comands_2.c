#include "minishell.h"

void	ft_commands_go_beginning(void)
{
	while (g_all.commands->prev != NULL)
		g_all.commands = g_all.commands->prev;
}
