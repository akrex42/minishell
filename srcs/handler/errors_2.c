#include "minishell.h"

int	ft_comp_to_spec(t_tokens_list *token)
{
	if (token == NULL)
		return (1);
	return ((!ft_strncmp(token->content, "|", 2)
			|| !ft_strncmp(token->content, ">", 2)
			|| !ft_strncmp(token->content, ">>", 3)
			|| !ft_strncmp(token->content, "<", 2)
			|| !ft_strncmp(token->content, ";", 2))
		&& token->special_value);
}

int	ft_syntax_error_2(void)
{
	if ((g_all.tokens->content[0] == ';' || g_all.tokens->content[0] == '|')
		&& ft_comp_to_spec(g_all.tokens->prev))
	{
		ft_putstr_fd("my_bash: syntax error near unexpected token `", 2);
		ft_putstr_fd(g_all.tokens->content, 2);
		ft_putstr_fd("'\n", 2);
		g_all.exit_status = 258;
		return (1);
	}
	else if ((g_all.tokens->content[0] == '<'
			|| g_all.tokens->content[0] == '>')
		&& ft_comp_to_spec(g_all.tokens->next))
	{
		ft_putstr_fd("my_bash: syntax error near unexpected token `", 2);
		if (g_all.tokens->next != NULL)
			ft_putstr_fd(g_all.tokens->next->content, 2);
		else
			ft_putstr_fd("newline", 2);
		ft_putstr_fd("'\n", 2);
		g_all.exit_status = 258;
		return (1);
	}
	return (0);
}

int	ft_syntax_error(void)
{
	ft_tokens_to_beginning();
	while (g_all.tokens)
	{
		if (ft_comp_to_spec(g_all.tokens))
		{
			if (ft_syntax_error_2())
				return (1);
		}
		if (g_all.tokens->next == NULL)
			break ;
		else
			g_all.tokens = g_all.tokens->next;
	}
	ft_tokens_to_beginning();
	return (0);
}
