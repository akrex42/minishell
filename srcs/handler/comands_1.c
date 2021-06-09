#include "minishell.h"

int	ft_compare_prog_to_redirect(void)
{
	if (g_all.commands == NULL)
		return (0);
	return (!ft_strncmp(g_all.commands->special, ">", 2) ||
			!ft_strncmp(g_all.commands->special, ">>", 3) ||
			!ft_strncmp(g_all.commands->special, "<", 2));
}

int	ft_compare_tokens_cont_to_spec(void)
{
	if (g_all.tokens == NULL)
		return (1);
	return ((!ft_strncmp(g_all.tokens->content, "|", 2) ||
			!ft_strncmp(g_all.tokens->content, ">", 2) ||
			!ft_strncmp(g_all.tokens->content, ">>", 3) ||
			!ft_strncmp(g_all.tokens->content, "<", 2) ||
			!ft_strncmp(g_all.tokens->content, ";", 2)) &&
			g_all.tokens->special_value);
}

int	ft_progs_count_args(void)
{
	int	len;
	int	j;

	len = 0;
	while (!ft_compare_tokens_cont_to_spec())
	{
		len++;
		if (g_all.tokens->next == NULL)
			break ;
		ft_tokens_step_front();
	}
	j = len;
	if (!(g_all.tokens->next) && !ft_compare_tokens_cont_to_spec())
			j--;
	while (j > 0)
	{
		ft_tokens_step_back();
		j--;
	}
	return (len);
}

void	ft_tokens_go_next_spec(void)
{
	while (!ft_compare_tokens_cont_to_spec())
	{
		if (g_all.tokens->next == NULL)
			break ;
		ft_tokens_step_front();
	}
	ft_tokens_step_front();
}

void	ft_new_prog_node(void)
{
	t_comands_list	*new;

	new = malloc(sizeof(t_comands_list));
	if (!new)
		ft_malloc_error();
	new->next = NULL;
	new->prog = NULL;
	new->args = NULL;
	new->used = 0;
	ft_bzero(new->special, 3);
	if (g_all.commands == NULL)
	{
		g_all.commands = new;
		g_all.commands->prev = NULL;
		return ;
	}
	while (g_all.commands->next != NULL)
		g_all.commands = g_all.commands->next;
	g_all.commands->next = new;
	new->prev = g_all.commands;
	g_all.commands = new;
}
