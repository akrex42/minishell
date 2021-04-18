/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzombie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 21:15:50 by yzombie           #+#    #+#             */
/*   Updated: 2020/11/03 21:15:51 by yzombie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memset(void *dest, int c, size_t n)
{
	int					i;
	unsigned char		*buf;

	i = 0;
	buf = (unsigned char *)dest;
	while (i < (int)n)
	{
		buf[i] = c;
		i++;
	}
	return (&buf[0]);
}
