/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzombie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 15:56:50 by yzombie           #+#    #+#             */
/*   Updated: 2020/11/07 15:56:51 by yzombie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	char	c;
	int		sign;

	sign = 1;
	if (n < 0)
	{
		write(fd, "-", 1);
		sign = -1;
	}
	if ((n >= 0 && n < 10) || (n > -10 && n <= 0))
	{
		c = (n % 10) * sign + '0';
		write(fd, &c, 1);
		return ;
	}
	if (sign == 1)
		ft_putnbr_fd(n / 10, fd);
	else
		ft_putnbr_fd((n / 10) * -1, fd);
	c = (n % 10) * sign + '0';
	write(fd, &c, 1);
}
