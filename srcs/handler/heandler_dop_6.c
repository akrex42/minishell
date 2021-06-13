#include "minishell.h"

int	ft_execute_2(void)
{
	g_all.fd_in = -1;
	g_all.fd_out = -1;
	g_all.pipes = NULL;
	g_all.pid = NULL;
	if (ft_make_redirect_fd() == -1)
		return (1);
	ft_make_pipes();
	ft_make_pid();
	signal(SIGINT, ft_sighnd_exec);
	signal(SIGQUIT, ft_sighnd_exec);
	ft_reset_input_mode();
	ft_skip_redirect();
	return (0);
}

void	ft_execute_3(void)
{
	ft_wait_pid();
	ft_set_input_mode(&g_all);
	signal(SIGINT, ft_sighnd);
	signal(SIGQUIT, ft_sighnd);
	ft_free_pipes();
	ft_free_pid();
}

void	ft_execute_5(void)
{
	int	i;

	i = 0;
	while (g_all.pipes)
	{
		ft_skip_redirect();
		ft_execute_program(g_all.pipes[i], g_all.pipes[i + 1], i);
		i++;
		if (g_all.commands->next == NULL)
			break ;
		else
			g_all.commands = g_all.commands->next;
	}
}

void	ft_execute(void)
{
	if (ft_execute_2())
		return ;
	if (ft_count_progs() == 1 && ft_check_builtins())
	{
		if (g_all.fd_out == -1)
			g_all.fd_out = 1;
		if (!ft_strncmp(g_all.commands->prog, "exit", 5))
			ft_putstr_fd("exit\n", 1);
		ft_execute_builtins();
		g_all.exit_status = g_all.exec.ret;
	}
	else
		ft_execute_5();
	ft_execute_3();
}
