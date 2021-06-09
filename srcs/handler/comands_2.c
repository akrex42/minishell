#include "minishell.h"

void	ft_commands_go_beginning(void)
{
	while (g_all.commands->prev != NULL)
		g_all.commands = g_all.commands->prev;
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

void	ft_free_comands_1(void)
{
	int	i;

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

void	ft_free_comands_2(void)
{
	int	i;

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
}

void	ft_free_comands(void)
{
	if (!g_all.commands)
		return ;
	ft_commands_go_beginning();
	while (g_all.commands->next)
		ft_free_comands_1();
	if (g_all.commands->prog != NULL)
		free(g_all.commands->prog);
	ft_free_comands_2();
	g_all.commands = NULL;
}

