/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzombie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 04:33:07 by yzombie           #+#    #+#             */
/*   Updated: 2020/11/04 04:33:09 by yzombie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memccpy(void *restrict dst,
	const void *restrict src, int c, size_t n)
{
	int				i;
	unsigned char	*buf;
	unsigned char	*from;
	unsigned char	ch;

	i = 0;
	buf = (unsigned char *)dst;
	from = (unsigned char *)src;
	ch = (unsigned char)c;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (i < (int)n && from[i] != ch)
	{
		buf[i] = from[i];
		i++;
	}
	if (from[i] != (int)n && from[i] == ch)
	{
		buf[i] = from[i];
		return (&buf[i + 1]);
	}
	return (NULL);
}
