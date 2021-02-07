/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 18:49:11 by alancel           #+#    #+#             */
/*   Updated: 2021/02/07 06:38:10 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mshell.h"

#define SIZE 2048

char	*pwd_util(void)
{
	char			*str;
	unsigned int	tmp;

	tmp = SIZE;
	str = malloc(tmp);
	while (true)
	{
		if (getcwd(str, tmp))
		{
			return (str);
		}
		else
		{
			free(str);
			if (errno != ERANGE)
				return (NULL);
			tmp += SIZE;
			str = malloc(tmp);
		}
	}
}

void	ft_pwd(void)
{
	char *str;

	str = pwd_util();
	ft_putendl_fd(str, 1);
}
