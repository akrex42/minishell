#include "minishell.h"

int	ft_is_relative(void)
{
	if (ft_strrchr(g_all.commands->prog, '/') != NULL)
		return (1);
	return (0);	
}
