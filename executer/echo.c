/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 19:00:56 by alancel           #+#    #+#             */
/*   Updated: 2021/02/08 18:59:04 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mshell.h"

void		ft_env(t_d_list *env_lst)
{
	t_env	*env;

	while (env_lst)
	{
		env = env_lst->content;
		if (ft_strcmp(env->key, "?"))
		{
			if (env->vlm)
			{
				ft_putstr_fd(env->key, 1);
				ft_putstr_fd(env->vlm, 1);
				write(1, "\n", 1);
			}
		}
		env_lst = env_lst->next;
	}
}

static int	check_flag(char *str)
{
	int i;
	int check;

	check = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '-')
		{
			check++;
			i++;
		}
		if (str[i] && (str[i] != 'n' || check > 1))
			return (0);
		i++;
	}
	return (1);
}

void		ft_echo(char **av)
{
	int flag;
	int i;

	flag = 0;
	i = 0;
	if (av[1] && check_flag(av[1]))
	{
		flag = 1;
		i++;
	}
	while (av[++i])
	{
		write(1, av[i], strlen(av[i]));
		if (av[i + 1])
			write(1, " ", 1);
	}
	if (flag == 0)
		write(1, "\n", 1);
}
