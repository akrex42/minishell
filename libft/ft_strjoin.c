/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzombie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 17:32:03 by yzombie           #+#    #+#             */
/*   Updated: 2020/11/06 17:32:04 by yzombie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len1;
	int		len2;
	char	*ret;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = len1 + ft_strlen(s2);
	ret = malloc(sizeof(char) * (len2 + 1));
	if (ret)
	{
		ft_strlcpy(ret, s1, len1 + 1);
		ft_strlcat(ret, s2, len2 + 1);
	}
	return (ret);
}
