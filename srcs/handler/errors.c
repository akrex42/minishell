#include "minishell.h"

int	ft_error_handler_2(void)
{
	if (!ft_strncmp(g_all.commands->prog, ".", 2))
	{
		ft_putstr_fd("my_bash: ", 2);
		ft_putstr_fd(g_all.commands->prog, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd("filename argument required", 2);
		ft_putchar_fd('\n', 2);
		ft_putstr_fd(".: usage: . filename [arguments]", 2);
		g_all.exec.ret = 2;
		return (1);
	}
	else if (!ft_strncmp(g_all.commands->prog, "..", 3))
	{
		ft_putstr_fd("my_bash: ", 2);
		ft_putstr_fd(g_all.commands->prog, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd("command not found", 2);
		g_all.exec.ret = 127;
		return (1);
	}
	return (0);
}

void	ft_error_handler_5(int errno_exec, void	**dir)
{
	(*dir) = opendir(g_all.commands->prog);
	if ((*dir) != NULL || errno == 13)
	{
		ft_putstr_fd(strerror(21), 2);
		g_all.exec.ret = 126;
	}
	else if (errno_exec == 13)
	{
		ft_putstr_fd(strerror(13), 2);
		g_all.exec.ret = 126;
	}
	else if (errno == 20)
	{
		ft_putstr_fd(strerror(errno), 2);
		g_all.exec.ret = 126;
	}
}

void	ft_error_handler_4(int errno_exec, void	**dir)
{
	(*dir) = opendir(g_all.commands->prog);
	if (errno == 20)
	{
		ft_putstr_fd(strerror(20), 2);
		g_all.exec.ret = 126;
	}
	else if (errno == 2)
	{
		ft_putstr_fd(strerror(errno_exec), 2);
		g_all.exec.ret = 127;
	}
	if ((*dir) != NULL)
		closedir((*dir));
}

void	ft_error_handler_3(int errno_exec, void	**dir)
{
	ft_putstr_fd("my_bash: ", 2);
	ft_putstr_fd(g_all.commands->prog, 2);
	ft_putstr_fd(": ", 2);
	if (!ft_is_relative() && errno_exec == 2)
	{
		ft_putstr_fd("command not found", 2);
		g_all.exec.ret = 127;
	}
	else if (errno_exec == 2)
		ft_error_handler_4(errno_exec, dir);
	else
		ft_error_handler_5(errno_exec, dir);
}

void	ft_error_handler(int errno_exec)
{
	void	*dir;

	dir = NULL;
	if (errno_exec != 8 && errno_exec != 0 && errno_exec != 1)
	{
		if (ft_error_handler_2())
			(void)dir;
		else
			ft_error_handler_3(errno_exec, &dir);
		ft_putstr_fd("\n", 2);
	}
	if (dir != NULL)
		closedir(dir);
	if (g_all.exit_status == 500)
		g_all.exec.ret = 130;
	if (g_all.exit_status == 501)
		g_all.exec.ret = 131;
	g_all.exit_status = g_all.exec.ret;
}
