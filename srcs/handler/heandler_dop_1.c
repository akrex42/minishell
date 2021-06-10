#include "minishell.h"

void	ft_go_to_right_prog(int i)
{
	int	j;

	j = 0;
	ft_commands_go_beginning();
	while (j != i)
	{
		ft_skip_redirect();
		if (g_all.commands->special[0] == '>'
			|| g_all.commands->special[0] == '<')
			break ;
		if (g_all.commands->prog == NULL)
		{
			g_all.commands = g_all.commands->next;
			continue ;
		}
		j++;
		g_all.commands = g_all.commands->next;
	}
}

void	ft_wait_pid(void)
{
	int	i;

	if (!g_all.pid)
		return ;
	i = 0;
	while (g_all.pid[i])
	{
		if (g_all.pid[i][0] != -1)
		{
			waitpid(g_all.pid[i][0], &g_all.exec.ret, 0);
			g_all.exec.ret = WEXITSTATUS(g_all.exec.ret);
			ft_go_to_right_prog(i);
			ft_error_handler(g_all.exec.ret);
		}
		i++;
	}
}

int	ft_move_redirect_2(void)
{
	if (g_all.tokens->next == NULL)
		return (1);
	else
		g_all.tokens = g_all.tokens->next;
	return (0);
}

void	ft_move_redirect(void)
{
	t_tokens_list	*token;

	ft_tokens_to_beginning();
	while (1)
	{
		if (g_all.tokens->next == NULL)
			break ;
		if ((g_all.tokens->content[0] == '>'
				|| g_all.tokens->content[0] == '<')
			&& !ft_comp_to_spec(g_all.tokens->next->next)
			&& g_all.tokens->prev != NULL)
		{
			token = g_all.tokens->next->next;
			g_all.tokens->prev->next = token;
			token->prev = g_all.tokens->prev;
			g_all.tokens->next->next = token->next;
			if (token->next != NULL)
				token->next->prev = g_all.tokens->next;
			token->next = g_all.tokens;
			g_all.tokens->prev = token;
			continue ;
		}
		if (ft_move_redirect_2())
			break ;
	}
}

void	ft_free_command_node(void)
{
	int				i;
	t_comands_list	*tmp;

	i = 0;
	while (g_all.commands->args[i])
	{
		free(g_all.commands->args[i]);
		i++;
	}
	free(g_all.commands->args[i]);
	free(g_all.commands->args);
	free(g_all.commands->prog);
	tmp = g_all.commands->next;
	g_all.commands = g_all.commands->prev;
	free(g_all.commands->next);
	g_all.commands->next = tmp;
	tmp->prev = g_all.commands;
}
