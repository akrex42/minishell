#include "minishell.h"

int	ft_make_redirect_fd_3(void)
{
	if (g_all.commands->special[0] == '<' && !(g_all.commands->used))
	{
		if (g_all.fd_in != -1)
			close(g_all.fd_in);
		g_all.fd_in = open(g_all.commands->prog, O_RDONLY, NULL);
		if (g_all.fd_in == -1 && errno != 14)
			return (ft_redirect_error());
		g_all.commands->used = 1;
	}
	return (0);
}

int	ft_make_redirect_fd_2(void)
{
	if (g_all.commands->special[0] == '>' && !(g_all.commands->used))
	{
		if (g_all.fd_out != -1)
			close(g_all.fd_out);
		g_all.fd_out = open(g_all.commands->prog,
				O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
		if (g_all.fd_out == -1 && errno != 14)
			return (ft_redirect_error());
		g_all.commands->used = 1;
	}
	return (0);
}

int	ft_make_redirect_fd_1(void)
{
	if (!ft_strncmp(g_all.commands->special, ">>", 3)
		&& !(g_all.commands->used))
	{
		if (g_all.fd_out != -1)
			close(g_all.fd_out);
		g_all.fd_out = open(g_all.commands->prog,
				O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
		if (g_all.fd_out == -1 && errno != 14)
			return (ft_redirect_error());
		g_all.commands->used = 1;
	}
	return (0);
}

int	ft_make_redirect_fd(void)
{
	t_comands_list	*tmp;
	int				ret;

	tmp = g_all.commands;
	while (1)
	{
		ret = ft_make_redirect_fd_1();
		if (ret == -1)
			return (ret);
		ret = ft_make_redirect_fd_2();
		if (ret == -1)
			return (ret);
		ret = ft_make_redirect_fd_3();
		if (ret == -1)
			return (ret);
		if (g_all.commands->next == NULL)
			break ;
		g_all.commands = g_all.commands->next;
	}
	g_all.commands = tmp;
	return (0);
}

int	ft_redirect_error(void)
{
	ft_putstr_fd("my_bash: ", 2);
	ft_putstr_fd(g_all.commands->prog, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	g_all.exit_status = 1;
	return (-1);
}
