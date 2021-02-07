/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 15:16:39 by mcottonm          #+#    #+#             */
/*   Updated: 2020/11/01 17:18:47 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*a;
	int		i;

	i = 0;
	a = (char*)malloc(ft_strlen(str) + 1);
	if (!a)
		return (0);
	while (str[i])
	{
		a[i] = str[i];
		i++;
	}
	a[i] = str[i];
	return (a);
}
