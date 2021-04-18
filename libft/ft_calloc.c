/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzombie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 14:08:23 by yzombie           #+#    #+#             */
/*   Updated: 2020/11/06 14:08:23 by yzombie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ret;
	int				i;

	ret = malloc(size * count);
	if (ret == NULL)
		return (NULL);
	i = count * (int)size;
	while (i-- > 0)
		ret[i] = '\0';
	return (ret);
}
