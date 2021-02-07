/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 15:10:10 by mcottonm          #+#    #+#             */
/*   Updated: 2020/11/07 20:36:41 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *arr, int c, size_t n)
{
	const unsigned char		sym = c;
	const unsigned char		*ptr;

	ptr = arr;
	while (n--)
	{
		if (*ptr == sym)
			return ((void *)ptr);
		ptr++;
	}
	return (NULL);
}
