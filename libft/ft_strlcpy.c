/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 16:16:41 by mcottonm          #+#    #+#             */
/*   Updated: 2020/11/02 15:07:23 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	char		*d;
	const char	*s = src;
	size_t		n;

	if (!dst || !src)
		return (0);
	n = size;
	d = dst;
	if (n)
	{
		while (--n)
		{
			if ((*d++ = *s++) == '\0')
				break ;
		}
	}
	if (!n)
	{
		if (size)
			*d = '\0';
		while (*s++)
			;
	}
	return (s - src - 1);
}
