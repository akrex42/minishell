#include "minishell.h"

void	ft_close_file_fd(void)
{
	if (g_all.fd_in != -1 && !(g_all.commands->prev != NULL 
		&& g_all.commands->prev->special[0] == '|'))
	{
		close(g_all.fd_in);
		g_all.fd_in = -1;
	}
	if (g_all.fd_out != -1 && !(g_all.commands->next != NULL &&
		g_all.commands->special[0] == '|'))
	{
		close(g_all.fd_out);
		g_all.fd_out = -1;
	}
}

int	ft_check_builtins(void)
{
	if (g_all.commands->prog != NULL && (!ft_strncmp("cd", 
			g_all.commands->prog, 3) || !ft_strncmp("echo", 
			g_all.commands->prog, 5) ||
		!ft_strncmp("env", g_all.commands->prog, 4) ||
		!ft_strncmp("exit", g_all.commands->prog, 5) ||
		!ft_strncmp("export", g_all.commands->prog, 7) ||
		!ft_strncmp("pwd", g_all.commands->prog, 4) ||
		!ft_strncmp("unset", g_all.commands->prog, 6)))
			return (1);
	return (0);
}

void	ft_execute_builtins(void)
{
	if (!ft_strncmp("cd", g_all.commands->prog, 3))
		g_all.exec.ret = ft_cd(g_all.commands->args);
	else if (!ft_strncmp("echo", g_all.commands->prog, 5))
		g_all.exec.ret = ft_echo(g_all.commands->args);
	else if (!ft_strncmp("env", g_all.commands->prog, 4))
		g_all.exec.ret = ft_env(g_all.commands->args);
	else if (!ft_strncmp("exit", g_all.commands->prog, 5))
		g_all.exec.ret = ft_exit(g_all.commands->args);
	else if (!ft_strncmp("export", g_all.commands->prog, 7))
		g_all.exec.ret = ft_export(g_all.commands->args);
	else if (!ft_strncmp("pwd", g_all.commands->prog, 4))
		g_all.exec.ret = ft_pwd(g_all.commands->args);
	else if (!ft_strncmp("unset", g_all.commands->prog, 6))
		g_all.exec.ret = ft_unset(g_all.commands->args);
}

void	ft_close_pipes(void)
{
	int	i;

	i = 0;
	while (g_all.pipes[i])
	{
		close(g_all.pipes[i][0]);
		close(g_all.pipes[i][1]);
		i++;
	}
}

int	ft_count_progs(void)
{
	int	i;

	i = 0;
	ft_commands_go_beginning();
	while (g_all.commands)
	{
		ft_skip_redirect();
		if (g_all.commands->special[0] == '>'
			|| g_all.commands->special[0] == '<')
			break ;
		if (g_all.commands->prog != NULL)
			i++;
		if (g_all.commands->next != NULL)
			g_all.commands = g_all.commands->next;
		else
			break ;
	}
	ft_commands_go_beginning();
	return (i);
}