/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzombie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 21:34:55 by yzombie           #+#    #+#             */
/*   Updated: 2020/11/03 21:34:56 by yzombie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	int				i;
	unsigned char	*buf;
	unsigned char	*from;

	i = 0;
	buf = (unsigned char *)dst;
	from = (unsigned char *)src;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (i < (int)n)
	{
		buf[i] = from[i];
		i++;
	}
	return (&buf[0]);
}
