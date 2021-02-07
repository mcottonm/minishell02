/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:41:38 by mcottonm          #+#    #+#             */
/*   Updated: 2020/11/06 14:14:05 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	lengn(int n)
{
	int ten;

	ten = 1;
	while (n / ten / 10)
		ten *= 10;
	return (ten);
}

void		ft_putnbr_fd(int n, int fd)
{
	int		ten;
	long	numb;
	int		i;

	i = 0;
	numb = (long)n;
	ten = lengn(n);
	if (numb < 0)
	{
		write(fd, "-", 1);
		numb = numb * -1;
	}
	while (ten)
	{
		i = numb / ten + '0';
		write(fd, &i, 1);
		numb %= ten;
		ten /= 10;
	}
}
