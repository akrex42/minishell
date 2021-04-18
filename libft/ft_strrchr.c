/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzombie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:02:12 by yzombie           #+#    #+#             */
/*   Updated: 2020/11/02 14:02:14 by yzombie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*ft_strrchr(const char *str, int ch)
{
	int		i;
	int		j;
	char	*ret;

	ret = (char *)str;
	i = 0;
	j = -1;
	while (str[i])
	{
		if (str[i] == ch)
			j = i;
		i++;
	}
	if (ch == '\0')
		return (&ret[i]);
	if (j != -1)
		return (&ret[j]);
	return (NULL);
}
