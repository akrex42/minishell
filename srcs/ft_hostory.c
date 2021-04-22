/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hostory.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzombie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 17:46:39 by yzombie           #+#    #+#             */
/*   Updated: 2021/04/18 17:46:40 by yzombie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general.h"

void	ft_init_hostory(t_hystory_list **history)
{
	*history = malloc(sizeof(t_hystory_list));
	if (!(*history))
		ft_malloc_error();
	(*history)->content = NULL;
	(*history)->prev = NULL;
	(*history)->next = NULL;
}

// добавляет новый элемент истории в конец и возвращает на него указатель
void	ft_history_newline(t_hystory_list **history,
					char *content)
{
	t_hystory_list	*new;

	new = malloc(sizeof(t_hystory_list));
	if (!new)
		ft_malloc_error();
	while ((*history)->next != NULL)
			history = &((*history)->next);
	new->prev = (*history)->prev;
	if ((*history)->prev != NULL)
		(*history)->prev->next = new;
	(*history)->prev = new;
	new->next = *history;
	new->content = content;
}

// шаг назад по истории если есть куда
void	ft_history_step_back(t_hystory_list **history)
{
	if ((*history)->prev == NULL)
		return ;
	(*history) = (*history)->prev;
}

// шаг вперед по истории если есть куда
void	ft_history_step_front(t_hystory_list **history)
{
	if ((*history)->next == NULL)
		return ;
	(*history) = (*history)->next;
}
