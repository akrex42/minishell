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
			if (dir != NULL || errno == 13)
				ft_putstr_fd("is a directory", 1);
			else if (errno == 20 && errno_exec == 13)
				ft_putstr_fd(strerror(errno_pred), 1);
		}
		ft_putstr_fd("\n", 1);
	}
	if (dir != NULL)
		closedir(dir);
	if (g_all.exit_status == 500)
		g_all.exec.ret = 130;
	if (g_all.exit_status == 501)
		g_all.exec.ret = 131;
	g_all.exit_status = g_all.exec.ret;
}

int	ft_syntax_error(void)
{
	ft_commands_go_beginning();
	while (1)
	{
		if (g_all.comands->prog == NULL)
		{
			if (g_all.comands->special[0] == '|')
				ft_putstr_fd("my_bash: syntax error near unexpected token `|'\n", 1);
			else if (g_all.comands->special[0] == ';')
				ft_putstr_fd("my_bash: syntax error near unexpected token `;'\n", 1);
			else
				ft_putstr_fd("my_bash: syntax error near unexpected token `newline'\n", 1);
			g_all.exit_status = 258;
			return 1;
		}
		// if (g_all.comands->special)
		if (g_all.comands->next == NULL)
			break ;
		else
			g_all.comands = g_all.comands->next;
	}
	ft_commands_go_beginning();
	return 0;
}
