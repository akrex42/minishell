#include "minishell.h"

void	ft_init_history(t_history_list **history)
{
	*history = malloc(sizeof(t_history_list));
	if (!(*history))
		ft_malloc_error();
	(*history)->content = NULL;
	(*history)->prev = NULL;
	(*history)->next = NULL;
}

// добавляет новый элемент истории в конец и возвращает на него указатель
void	ft_history_newline(t_history_list **history,
			char *content)
{
	t_history_list	*new;

	if (!ft_strncmp(content, "", 1))
		return ;
	new = malloc(sizeof(t_history_list));
	if (!new)
		ft_malloc_error();
	while ((*history)->next != NULL)
		*history = (*history)->next;
	new->content = content;
	new->prev = (*history)->prev;
	new->next = *history;
	if (new->prev != NULL)
		new->prev->next = new;
	(*history)->prev = new;
}

// шаг назад по истории если есть куда
void	ft_history_step_back(t_history_list **history)
{
	if ((*history)->prev == NULL)
		return ;
	(*history) = (*history)->prev;
}

// шаг вперед по истории если есть куда
void	ft_history_step_front(t_history_list **history)
{
	if ((*history)->next == NULL)
		return ;
	(*history) = (*history)->next;
}
