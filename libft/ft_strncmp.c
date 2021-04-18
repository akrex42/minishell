/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzombie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:44:27 by yzombie           #+#    #+#             */
/*   Updated: 2020/11/02 16:44:29 by yzombie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	int		i;

	if (!n)
		return (0);
	i = 0;
	while (i < (int)n)
	{
		if (str1[i] != str2[i] || (!str1[i] && !str2[i]))
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	i--;
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}
