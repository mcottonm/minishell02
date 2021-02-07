/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 15:05:43 by mcottonm          #+#    #+#             */
/*   Updated: 2020/10/30 16:41:32 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void *a;

	a = (void*)malloc(count * size);
	if (!a)
		return (0);
	ft_memset(a, 0, count * size);
	return (a);
}
