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

// добавляет новый элемент истории в конец и возвращает на него указатель
t_hystory_list	*ft_history_newline(t_hystory_list **history,
					char *content)
{
	t_hystory_list	*new;

	new = malloc(sizeof(t_hystory_list));
	if (!new)
		ft_malloc_error();
	if (*history != NULL)
	{
		while ((*history)->next != NULL)
			history = &((*history)->next);
		(*history)->next = new;
		new->prev = *history;
	}
	else
		new->prev = NULL;
	new->content = content;
	new->next = NULL;
	return (new);
}

// 1 - отображаем строку истории; 0 - ничего не отображаем
void	ft_history_step_back(t_hystory_list **history)
{
	if ((*history) == NULL || (*history)->prev == NULL)
		return ;
	(*history) = (*history)->prev;
}

// 1 - отображаем строку истории; 0 - отображаем сущкствующую строку
int	ft_history_step_front(t_hystory_list **history)
{
	if ((*history) == NULL || (*history)->next == NULL)
		return (0);
	(*history) = (*history)->next;
	return (1);
}
