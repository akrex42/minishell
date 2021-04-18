/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzombie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 17:42:49 by yzombie           #+#    #+#             */
/*   Updated: 2020/11/06 17:42:50 by yzombie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	check_char(char const ch, char const *set)
{
	int		i;

	i = 0;
	while (set[i])
	{
		if (ch == set[i])
			return (0);
		i++;
	}
	return (1);
}

static char	*ft_strtrim_2(const char *s1, char *ret, int min_i, int max_i)
{
	int		i;
	int		j;

	i = min_i;
	j = 0;
	while (i <= max_i)
		ret[j++] = s1[i++];
	ret[j] = '\0';
	return (ret);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	int		min_i;
	int		max_i;

	if (!s1 || !set)
		return (NULL);
	min_i = 0;
	max_i = ft_strlen(s1) - 1;
	while (!check_char(s1[max_i], set) && max_i > 0)
		max_i--;
	while (!check_char(s1[min_i], set) && min_i < max_i)
		min_i++;
	if (max_i > min_i)
		ret = malloc(sizeof(char) * (max_i - min_i + 2));
	else
		ret = malloc(sizeof(char));
	if (ret == NULL)
		return (NULL);
	if (min_i >= max_i)
	{
		ret[0] = '\0';
		return (ret);
	}
	return (ft_strtrim_2(s1, ret, min_i, max_i));
}
