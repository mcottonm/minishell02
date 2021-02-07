/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 15:55:42 by mcottonm          #+#    #+#             */
/*   Updated: 2020/10/31 13:17:11 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *arr1, const void *arr2, size_t n)
{
	const unsigned char	*tmp1 = arr1;
	const unsigned char	*tmp2 = arr2;
	size_t				i;
	int					s;

	i = 0;
	while (i++ < n)
	{
		s = *(tmp1++) - *(tmp2++);
		if (s)
			return (s);
	}
	return (0);
}
