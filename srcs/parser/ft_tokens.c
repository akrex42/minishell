#include "minishell.h"

void	ft_tokens_to_beginning(void)
{
	while (g_all.tokens->prev != NULL)
		g_all.tokens = g_all.tokens->prev;
}

void	ft_display_tokens(void)
{
	if (!g_all.tokens)
	{
		ft_putstr_fd("(null)\n", 1);
		return ;
	}
	ft_tokens_to_beginning();
	while (g_all.tokens->next != NULL)
	{
		printf("%s\n", g_all.tokens->content);
		g_all.tokens = g_all.tokens->next;
	}
	printf("%s\n", g_all.tokens->content);
}

void	ft_free_tokens(void)
{
	if (!g_all.tokens)
		return ;
	ft_tokens_to_beginning();
	while (g_all.tokens->next != NULL)
	{
		g_all.tokens = g_all.tokens->next;
		free(g_all.tokens->prev->content);
		free(g_all.tokens->prev);
	}
	free(g_all.tokens->content);
	free(g_all.tokens);
	g_all.tokens = NULL;
}

// добавляет новый элемент истории в конец и возвращает на него указатель
void	ft_tokens_newline(char *content)
{
	t_tokens_list	*new;

	new = malloc(sizeof(t_tokens_list));
	if (!new)
		ft_malloc_error();
	new->next = NULL;
	new->content = content;
	if (g_all.tokens == NULL)
	{
		g_all.tokens = new;
		g_all.tokens->prev = NULL;
		return ;
	}
	while (g_all.tokens->next != NULL)
		g_all.tokens = g_all.tokens->next;
	g_all.tokens->next = new;
	new->prev = g_all.tokens;
	g_all.tokens = new;
}

// шаг назад по истории если есть куда
void	ft_tokens_step_back(void)
{
	if (g_all.tokens->prev == NULL)
		return ;
	g_all.tokens = g_all.tokens->prev;
}

// шаг вперед по истории если есть куда
void	ft_tokens_step_front(void)
{
	if (g_all.tokens->next == NULL)
		return ;
	g_all.tokens = g_all.tokens->next;
}