/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_joy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 13:00:28 by mcottonm          #+#    #+#             */
/*   Updated: 2021/01/28 13:01:34 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mshell.h"

void	put_fenv(d_list *env_lst)
{
	int		fd;
	t_env	*env;

	fd = open("fENV", O_RDWR | O_TRUNC | O_CREAT, 0666);
	while (env_lst)
	{
		env = env_lst->content;
		write(fd, env->key, ft_strlen(env->key));
		write(fd, "=", 1);
		write(fd, "\"", 1);
		write(fd, (env->vlm + 1), ft_strlen(env->vlm) - 1);
		write(fd, "\"", 1);
		write(fd, "\n", 1);
		env_lst = env_lst->next;
	}
	close(fd);
}

d_list	*take_fenv(d_list *env_lst)
{
	int		fd;
	char	*str;
	t_env	*env;
	d_list	*tmp;

	while (env_lst)
	{
		tmp = env_lst->next;
		ft_dlstdelone(env_lst, free);
		env_lst = tmp;
	}
	env_lst = 0;
	fd = open("fENV", O_RDWR | O_CREAT, 0666);
	while (get_next_line(fd, &str))
	{
		env = loc_env(str);
		ft_dlstadd_back(&env_lst, ft_dlstnew(env));
		env = env_lst->content;
		free(str);
	}
	close(fd);
	return (env_lst);
}
