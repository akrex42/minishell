/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzombie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 14:02:40 by yzombie           #+#    #+#             */
/*   Updated: 2020/11/06 14:02:41 by yzombie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*ft_strchr(const char *s, int c)
{
	char	*ret;
	char	find;

	find = (char)c;
	ret = (char *)s;
	while (*ret)
	{
		if (*ret == find)
			break ;
		ret++;
	}
	if (*ret == find)
		return (ret);
	return (NULL);
}
