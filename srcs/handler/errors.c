#include "minishell.h"

void	ft_error_handler(int errno_exec)
{
	void	*dir;

	dir = NULL;
	// ft_putnbr_fd(errno_exec, 1);
	if (errno_exec != 8 && errno_exec != 0 && errno_exec != 1)
	{
		ft_putstr_fd("my_bash: ", 2);
		ft_putstr_fd(g_all.comands->prog, 2);
		ft_putstr_fd(": ", 2);
		if (!ft_is_relative()) // FIXME
		{
			if (errno_exec == 2)
			{
				ft_putstr_fd("command not found", 2);
				g_all.exec.ret = 127;
			}
			if (errno_exec == 13)
			{
				ft_putstr_fd(strerror(13), 2);
				g_all.exec.ret = 126;
			}
		}
		else if (errno_exec == 2 || errno_exec == 20)
		{
			ft_putstr_fd(strerror(errno_exec), 2); // no such file or directory
			g_all.exec.ret = 1; // not really clear
		}
		else
		{
			dir = opendir(g_all.comands->prog);
			if (dir != NULL || errno == 13)
				ft_putstr_fd(strerror(21), 2); // is a directory
			else if (errno == 13)
				ft_putstr_fd(strerror(13), 2); // permission denied
			else if (errno == 20 && errno_exec == 13)
				ft_putstr_fd(strerror(errno), 2); // is not a directory
		}
		ft_putstr_fd("\n", 2);
	}
	if (dir != NULL)
		closedir(dir);
	if (g_all.exit_status == 500) // ???
		g_all.exec.ret = 130;
	if (g_all.exit_status == 501)
		g_all.exec.ret = 131;
	g_all.exit_status = g_all.exec.ret;
}

int	ft_syntax_error(void)
{
	ft_tokens_to_beginning();
	while (1)
	{
		if (g_all.tokens->content[0] == '|')
		{
			if (g_all.tokens->prev == NULL || g_all.tokens->next == NULL)
			{
				ft_putstr_fd("my_bash: syntax error near unexpected token `|'\n", 2);
				g_all.exit_status = 258;
				return 1;
			}
		}
		else if (g_all.tokens->content[0] == ';')
		{
			if (g_all.tokens->prev == NULL)
			{
				ft_putstr_fd("my_bash: syntax error near unexpected token `;'\n", 2);
				g_all.exit_status = 258;
				return 1;
			}
		}
		else if (g_all.tokens->content[0] == '>' || g_all.tokens->content[0] == '<')
		{
			if (g_all.tokens->next == NULL)
			{
				ft_putstr_fd("my_bash: syntax error near unexpected token `newline'\n", 2);
				g_all.exit_status = 258;
				return 1;
			}
		}
		if (g_all.tokens->next == NULL)
			break ;
		else
			g_all.tokens = g_all.tokens->next;
	}
	ft_tokens_to_beginning();
	return 0;
}
