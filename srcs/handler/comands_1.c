#include "minishell.h"

int	ft_compare_prog_to_redirect(void) // 1 - нашлось
{
	if (g_all.commands == NULL)
		return (0);
	return (!ft_strncmp(g_all.commands->special, ">", 2) ||
			!ft_strncmp(g_all.commands->special, ">>", 3) ||
			!ft_strncmp(g_all.commands->special, "<", 2));
}

int	ft_compare_tokens_cont_to_spec(void) // 1 - нашлось
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

void	ft_comands_list_add_args_and_prog(void)
{
	int	arg_len;
	int	i;

	arg_len = ft_progs_count_args();
	g_all.commands->args = malloc(sizeof(char *) * (arg_len + 1));
	i = 0;
	if (!ft_compare_tokens_cont_to_spec())
		g_all.commands->prog = ft_strdup(g_all.tokens->content);
	while (i < arg_len)
	{
		g_all.commands->args[i] = ft_strdup(g_all.tokens->content);
		ft_tokens_step_front();
		i++;
	}
	g_all.commands->args[i] = NULL;
	if (ft_compare_tokens_cont_to_spec())
		ft_strlcpy(g_all.commands->special, g_all.tokens->content, 3);
}

void	ft_free_comands(void)
{
	int	i;

	if (!g_all.commands)
		return ;
	ft_commands_go_beginning();
	while (g_all.commands->next)
	{
		if (g_all.commands->prog != NULL)
			free(g_all.commands->prog);
		i = 0;
		if (g_all.commands->args != NULL)
		{
			while (g_all.commands->args[i] != NULL)
			{
				free(g_all.commands->args[i]);
				i++;
			}
			free(g_all.commands->args);
		}
		g_all.commands = g_all.commands->next;
		free(g_all.commands->prev);
	}
	if (g_all.commands->prog != NULL) //! проверить
		free(g_all.commands->prog);
	i = 0;
	if (g_all.commands->args != NULL)
	{
		while (g_all.commands->args[i] != NULL)
		{
			free(g_all.commands->args[i]);
			i++;
		}
		free(g_all.commands->args);
	}
	free(g_all.commands);
	g_all.commands = NULL;
}

void	ft_display_comands(void)
{
	int	i;

	while (g_all.commands->prev != NULL)
		g_all.commands = g_all.commands->prev;
	while (g_all.commands->next != NULL)
	{
		ft_putstr_fd("prog: ", 1);
		ft_putstr_fd(g_all.commands->prog, 1);
		ft_putstr_fd("\n", 1);
		i = 0;
		ft_putstr_fd("args: ", 1);
		if (g_all.commands->args != NULL)
			while (g_all.commands->args[i] != NULL)
			{
				ft_putstr_fd("[", 1);
				ft_putstr_fd(g_all.commands->args[i], 1);
				ft_putstr_fd("] ", 1);
				i++;
			}
		ft_putstr_fd("\n", 1);
		ft_putstr_fd("spec: ", 1);
		ft_putstr_fd(g_all.commands->special, 1);		
		ft_putstr_fd("\n", 1);
		ft_putstr_fd("used: ", 1);
		ft_putnbr_fd(g_all.commands->used, 1);
		ft_putstr_fd("\n\n", 1);

		g_all.commands = g_all.commands->next;
	}
	ft_putstr_fd("prog: ", 1);
	ft_putstr_fd(g_all.commands->prog, 1);
	ft_putstr_fd("\n", 1);
	i = 0;
	ft_putstr_fd("args: ", 1);
	if (g_all.commands->args != NULL)
		while (g_all.commands->args[i] != NULL)
		{
			ft_putstr_fd("[", 1);
			ft_putstr_fd(g_all.commands->args[i], 1);
			ft_putstr_fd("] ", 1);
			i++;
		}
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("spec: ", 1);
	ft_putstr_fd(g_all.commands->special, 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("used: ", 1);
	ft_putnbr_fd(g_all.commands->used, 1);	
	ft_putstr_fd("\n\n", 1);
	ft_commands_go_beginning();
}
