#include "minishell.h"

void	ft_execute_program_1(int *fd2)
{
	if (ft_check_builtins())
	{
		if (g_all.commands->next != NULL
			&& g_all.commands->special[0] == '|')
			g_all.fd_out = fd2[1];
		else if (g_all.fd_out == -1)
			g_all.fd_out = 1;
		ft_execute_builtins();
		if (g_all.commands->next != NULL
			&& g_all.commands->special[0] == '|')
			close(fd2[1]);
		else if (g_all.fd_out != 1)
			close(g_all.fd_out);
		g_all.exit_status = g_all.exec.ret;
		exit (g_all.exit_status);
	}
}

void	ft_execute_program_2(int *fd1, int *fd2)
{
	if (g_all.commands->prev != NULL
		&& g_all.commands->prev->special[0] == '|')
		dup2(fd1[0], 0);
	else if (g_all.fd_in != -1)
	{
		dup2(g_all.fd_in, 0);
		close(g_all.fd_in);
	}
	if (g_all.commands->next != NULL
		&& g_all.commands->special[0] == '|')
		dup2(fd2[1], 1);
	else if (g_all.fd_out != -1)
	{
		dup2(g_all.fd_out, 1);
		close(g_all.fd_out);
	}
	ft_close_pipes();
}

void	ft_execute_program_4(void)
{
	int	i;

	ft_rewrite_path();
	g_all.exec.tmp = ft_strjoin("/", g_all.commands->prog);
	i = 0;
	if (!g_all.path)
		exit(128);
	while (g_all.path[i] != NULL)
	{
		g_all.exec.str = ft_strjoin(g_all.path[i], g_all.exec.tmp);
		execve(g_all.exec.str, g_all.commands->args, g_all.env);
		i++;
		free(g_all.exec.str);
	}
	free(g_all.exec.tmp);
}

void	ft_execute_program(int *fd1, int *fd2, int i)
{
	if (g_all.commands->special[0] == '>'
		|| g_all.commands->special[0] == '<')
		return ;
	if (!(g_all.pid[i]))
		return ;
	g_all.pid[i][0] = fork();
	if (!(g_all.pid[i][0]))
	{
		ft_execute_program_1(fd2);
		ft_execute_program_2(fd1, fd2);
		if (ft_is_relative())
			execve(g_all.commands->prog, g_all.commands->args, g_all.env);
		else
			ft_execute_program_4();
		exit(127);
	}
	close(fd1[0]);
	close(fd1[1]);
	ft_close_file_fd();
}

void	ft_handler(void)
{
	if (!(g_all.tokens))
		return ;
	ft_move_redirect();
	ft_syntax_analyzer();
	ft_commands_go_beginning();
	ft_execute();
}
