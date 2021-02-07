/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:48:58 by mcottonm          #+#    #+#             */
/*   Updated: 2020/11/06 14:12:05 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	const unsigned char		*tmps = src;
	unsigned char			*tmpd;
	size_t					i;

	if (!dst && !src)
		return (0);
	tmpd = dst;
	i = 0;
	if (dst > src)
		while (n--)
			tmpd[n] = tmps[n];
	else
		while (i < n)
			tmpd[i++] = *tmps++;
	return (dst);
}
