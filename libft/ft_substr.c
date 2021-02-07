/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:36:55 by mcottonm          #+#    #+#             */
/*   Updated: 2020/11/05 13:28:32 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*sstr;
	const char	*ss = s;
	int			i;

	if (!s || len == 0 || start >= ft_strlen(s))
		return (ft_strdup(""));
	if (!(sstr = (char*)malloc(len + 1)))
		return (0);
	i = 0;
	while (start--)
		ss++;
	while (len--)
		sstr[i++] = *ss++;
	sstr[i] = '\0';
	return (sstr);
}
