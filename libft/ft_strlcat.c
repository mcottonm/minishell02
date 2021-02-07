/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 17:47:56 by mcottonm          #+#    #+#             */
/*   Updated: 2020/10/31 16:33:29 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char	*d;
	size_t	len;

	d = dst;
	len = ft_strlen(dst);
	if (len >= size)
		return (size + ft_strlen(src));
	d = ft_memccpy(dst + len, src, '\0', size - len);
	if (!d)
		*(dst + size - 1) = '\0';
	return (ft_strlen(src) + len);
}
