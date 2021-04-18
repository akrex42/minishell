/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzombie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 14:01:35 by yzombie           #+#    #+#             */
/*   Updated: 2020/11/07 14:01:36 by yzombie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_count_chars(int n)
{
	int		count;

	count = 0;
	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static char	*ft_exception(int n)
{
	char	*ret;

	ret = NULL;
	if (n == -2147483648)
	{
		ret = malloc(sizeof(char) * 12);
		if (!ret)
			return (NULL);
		ft_strlcpy(ret, "-2147483648", 12);
		return (ret);
	}
	if (n == 0)
	{
		ret = malloc(sizeof(char) * 2);
		if (!ret)
			return (NULL);
		ret[0] = '0';
		ret[1] = '\0';
		return (ret);
	}
	return (ret);
}

static void	ft_if_n_negative(int *sign, int *count, int *n)
{
	*sign = 1;
	*n *= -1;
	(*count)++;
}

char		*ft_itoa(int n)
{
	char	*ret;
	int		count;
	int		sign;

	if (n == 0 || n == -2147483648)
		return (ft_exception(n));
	count = ft_count_chars(n);
	sign = 0;
	if (n < 0)
		ft_if_n_negative(&sign, &count, &n);
	ret = malloc(sizeof(char) * (count + 1));
	if (!ret)
		return (NULL);
	ret[count] = '\0';
	count--;
	while (count >= 0)
	{
		ret[count--] = n % 10 + '0';
		n /= 10;
	}
	if (sign)
		ret[0] = '-';
	return (ret);
}
