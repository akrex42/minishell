/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzombie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 15:36:39 by yzombie           #+#    #+#             */
/*   Updated: 2020/11/08 15:36:40 by yzombie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*temp;

	if (!lst)
		return (NULL);
	head = malloc(sizeof(t_list));
	if (!head)
		return (NULL);
	head->content = f(lst->content);
	temp = head;
	lst = lst->next;
	while (lst)
	{
		temp->next = malloc(sizeof(t_list));
		if (!temp->next)
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		temp = temp->next;
		temp->content = f(lst->content);
		lst = lst->next;
	}
	temp->next = NULL;
	return (head);
}
