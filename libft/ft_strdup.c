/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzombie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 15:19:03 by yzombie           #+#    #+#             */
/*   Updated: 2020/11/06 15:19:04 by yzombie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ret;
	int		len;

	len = ft_strlen(s1);
	ret = malloc(sizeof(char) * (len + 1));
	if (ret)
		ft_strlcpy(ret, s1, len + 1);
	return (ret);
}
