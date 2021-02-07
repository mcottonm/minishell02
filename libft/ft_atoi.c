/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 14:04:52 by mcottonm          #+#    #+#             */
/*   Updated: 2020/11/05 20:26:55 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int			i;
	int			at;
	int			p;

	i = 1;
	at = 0;
	if (!ft_strncmp(str, "-2147483648", 12))
		return (-2147483648);
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-')
		i = -1;
	if ((*str == '+') || (*str == '-'))
		str++;
	while (*str >= '0' && *str <= '9')
	{
		p = at;
		at = at * 10 - '0' + *str++;
		if ((p != at / 10 || at < 0))
			return ((i > 0) ? -1 : 0);
	}
	return (at * i);
}
