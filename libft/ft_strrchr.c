/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 19:01:55 by mcottonm          #+#    #+#             */
/*   Updated: 2020/11/04 16:22:08 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	char const	*p = 0;

	while (*str)
	{
		if (*str == ch)
			p = str;
		str++;
	}
	if (*str == ch)
		return ((char*)str);
	return ((char*)p);
}
