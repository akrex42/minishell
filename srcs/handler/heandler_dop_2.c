#include "minishell.h"

void	ft_syntax_analyzer_1(void)
{
	if (g_all.tokens->prev->prev != NULL)
		if (g_all.tokens->next == NULL && (g_all.commands->special[0] == '|' ||
			g_all.tokens->prev->prev->content[0] == '>' ||
			g_all.tokens->prev->prev->content[0] == '<'))
	{
		ft_tokens_step_front();
		ft_new_prog_node();
		ft_comands_list_add_args_and_prog();
	}
}

void	ft_syntax_analyzer_3(void)
{
	if (g_all.commands->prog == NULL)
	{
		if (g_all.tokens->next != NULL)
		{
			ft_tokens_step_front();
			g_all.commands->prog = ft_strdup(g_all.tokens->content);
		}
	}
	else
	{
		ft_new_prog_node();
		ft_strlcpy(g_all.commands->special, g_all.commands->prev->special, 3);
		if (g_all.tokens->next != NULL)
		{
			ft_tokens_step_front();
			g_all.commands->prog = ft_strdup(g_all.tokens->content);
		}
		ft_bzero(g_all.commands->prev->special, 3);
	}
}

void	ft_syntax_analyzer(void)
{
	ft_tokens_to_beginning();
	if (g_all.tokens->next == NULL)
	{
		ft_new_prog_node();
		ft_comands_list_add_args_and_prog();
		return ;
	}
	while (g_all.tokens->next != NULL)
	{
		ft_new_prog_node();
		ft_comands_list_add_args_and_prog();
		if (ft_compare_prog_to_redirect())
			ft_syntax_analyzer_3();
		ft_tokens_step_front();
	}
	ft_syntax_analyzer_1();
}
