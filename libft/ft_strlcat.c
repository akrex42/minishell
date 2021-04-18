/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzombie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 06:39:42 by yzombie           #+#    #+#             */
/*   Updated: 2020/11/04 06:39:42 by yzombie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *d, const char *s, size_t dstsize)
{
	int		n;
	int		ret;

	ret = ft_strlen(d) + ft_strlen(s);
	if (dstsize - 1 == ft_strlen(d))
		return (ret);
	n = dstsize;
	while (n-- && *d)
		d++;
	if (n <= 0)
		return (dstsize + ft_strlen(s));
	while (*s && n-- != 0)
		*d++ = *s++;
	*d = '\0';
	return (ret);
}
