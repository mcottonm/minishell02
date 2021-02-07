/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 17:54:40 by mcottonm          #+#    #+#             */
/*   Updated: 2020/11/06 14:14:24 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(int n, int *i)
{
	int ten;

	ten = 1;
	while (n / ten / 10)
	{
		ten *= 10;
		(*i)++;
	}
	if (n < 0)
		(*i)++;
	return (ten);
}

char		*ft_itoa(int n)
{
	int		i;
	int		ten;
	long	numb;
	char	*s;

	i = 0;
	numb = (long)n;
	ten = ft_len(n, &i);
	if (!(s = (char*)malloc(i + 2)))
		return (0);
	i = 0;
	if (numb < 0)
	{
		s[i++] = '-';
		numb = numb * -1;
	}
	while (ten)
	{
		s[i++] = numb / ten + '0';
		numb %= ten;
		ten /= 10;
	}
	s[i] = '\0';
	return (s);
}
