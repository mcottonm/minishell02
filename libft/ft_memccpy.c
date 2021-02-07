/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:02:55 by mcottonm          #+#    #+#             */
/*   Updated: 2020/11/05 13:46:10 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*tmpd;
	const unsigned char	*tmps = src;
	size_t				i;
	int					f;

	if ((!dst && !src) || !n)
		return (0);
	i = 0;
	f = 0;
	tmpd = dst;
	while (i < n)
	{
		*tmpd++ = *tmps;
		if (*tmps++ == (unsigned char)c)
		{
			f = 1;
			break ;
		}
		i++;
	}
	if (!f)
		return (0);
	return ((void*)tmpd);
}
