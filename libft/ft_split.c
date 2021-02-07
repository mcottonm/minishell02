/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 17:12:23 by mcottonm          #+#    #+#             */
/*   Updated: 2020/11/08 17:11:32 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_loc1(const char *s, char c)
{
	char		**str;
	int			j;

	j = 0;
	if (!s)
		return (0);
	while (s)
	{
		while (*s == c && *s)
			s++;
		if (*s == '\0')
			break ;
		if (!c && *s)
		{
			j = 1;
			break ;
		}
		s = ft_strchr(s, c);
		j++;
	}
	if (!(str = (char **)ft_calloc((j + 1), sizeof(char*))))
		return (0);
	return (str);
}

static void	ft_free(char **s)
{
	int i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}

static char	*ft_strdupf(const char *s, char **str)
{
	char	*strt;

	strt = 0;
	if (!(strt = ft_strdup(s)))
	{
		ft_free(str);
		return (0);
	}
	return (strt);
}

char		**ft_split(const char *s, char c)
{
	char	**str;
	char	**strt;

	str = ft_loc1(s, c);
	strt = str;
	while (s && strt && *s)
	{
		if (ft_strchr(s, c) && (*s != c) && *ft_strchr(s, c))
		{
			if (!(*(strt++) = ft_substr(s, 0, ft_strchr(s, c) - s)))
			{
				ft_free(str);
				return (0);
			}
			s = ft_strchr(s, c);
		}
		else if (*s != c)
		{
			if (!(*strt = ft_strdupf(s, str)))
				return (0);
			break ;
		}
		s++;
	}
	return (str);
}
