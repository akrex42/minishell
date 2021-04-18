/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzombie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 11:57:41 by yzombie           #+#    #+#             */
/*   Updated: 2020/11/07 11:57:42 by yzombie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_count(char const *s, int c)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != c && s[i])
				i++;
		}
		else if (s[i])
			i++;
	}
	return (count);
}

static int	ft_count_word(char const *s, int c, int i)
{
	int	count;

	count = 0;
	while (s[i] != c && s[i])
	{
		count++;
		i++;
	}
	return (count);
}

static char	**ft_split_2(char const *s, char c, char **ret)
{
	int		i;
	int		j;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
		if (s[i] != c)
		{
			ret[count] = malloc(ft_count_word(s, c, i) + 1);
			if (!ret[count])
				return (NULL);
			j = 0;
			while (s[i] != c && s[i])
			{
				ret[count][j++] = s[i];
				i++;
			}
			ret[count][j] = '\0';
			count++;
		}
		else if (s[i])
			i++;
	ret[count] = NULL;
	return (ret);
}

char		**ft_split(char const *s, char c)
{
	char	**ret;
	int		count;

	if (!s)
		return (NULL);
	count = ft_count(s, c);
	ret = malloc(sizeof(char *) * (count + 1));
	if (!ret)
		return (NULL);
	return (ft_split_2(s, c, ret));
}
