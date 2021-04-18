/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzombie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 15:58:13 by yzombie           #+#    #+#             */
/*   Updated: 2020/11/06 15:58:14 by yzombie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;

	if (!s)
		return (NULL);
	ret = malloc(sizeof(char) * (len + 1));
	if (ret && start >= ft_strlen(s))
	{
		ret[0] = '\0';
		return (ret);
	}
	if (ret)
		ft_strlcpy(ret, &s[start], len + 1);
	return (ret);
}
