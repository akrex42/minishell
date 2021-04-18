/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzombie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 15:44:28 by yzombie           #+#    #+#             */
/*   Updated: 2020/11/02 15:44:30 by yzombie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str_b, const char *str_a, size_t len)
{
	int		i;
	int		j;
	char	*ret;

	len -= ft_strlen(str_a);
	ret = (char *)str_b;
	if (!str_a[0])
		return (&ret[0]);
	i = 0;
	while (str_b[i] && i <= (int)len)
	{
		j = 0;
		while (str_b[i + j] == str_a[j] && str_b[i + j] && str_a[j])
			j++;
		if (!str_a[j])
			return (&ret[i]);
		i++;
	}
	return (NULL);
}
