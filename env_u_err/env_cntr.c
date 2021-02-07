/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cntr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 15:04:21 by mcottonm          #+#    #+#             */
/*   Updated: 2021/02/07 03:59:36 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mshell.h"

d_list	*srch_key(d_list *env_lst, const char *new)
{
	t_env	*env;

	if (!new)
		return (0);
	while (env_lst && env_lst->prev)
		env_lst = env_lst->prev;
	while (env_lst)
	{
		env = (t_env*)env_lst->content;
		if (!(ft_strcmp(env->key, new)))
			return (env_lst);
		env_lst = env_lst->next;
	}
	return (env_lst);
}

d_list	*srch_hide_key(d_list *env_lst, const char *new)
{
	t_env	*env;

	if (!new)
		return (0);
	while (env_lst)
	{
		env = (t_env*)env_lst->content;
		if (!(ft_strcmp(env->key, new)))
			return (env_lst);
		env_lst = env_lst->prev;
	}
	return (env_lst);
}

void	set_env(d_list *env_lst, const char *new, bool visible)
{
	t_env	*new_env;
	d_list	*lst;

	new_env = env_lst->content;
	new_env = loc_env(new);
	if ((lst = srch_key(env_lst, new_env->key)))
	{
		set_vlm(&lst->content, new_env);
		return ;
	}
	if ((lst = srch_hide_key(env_lst, new_env->key)))
	{
		set_vlm(&lst->content, new_env);
		if (!visible)
			return ;
	}
	if (!visible)
		ft_dlstadd_frnt(&env_lst, ft_dlstnew(new_env));
	else
		ft_dlstadd_back(&env_lst, ft_dlstnew(new_env));
}

void	unset_env(d_list *env_lst, const char *new)
{
	d_list	*tmp;

	if ((tmp = srch_key(env_lst, new)))
		ft_dlstdelone(tmp, free_env);
	else if ((env_lst = srch_hide_key(env_lst, new)))
		ft_dlstdelone(env_lst, free_env);
}

char	*env_vlm(d_list *env_lst, const char *new)
{
	t_env	*new_env;
	char	*ret;
	char	*tmp;

	if (!new)
		return (0);
	ret = 0;
	if ((env_lst = srch_key(env_lst, new)))
	{
		new_env = (t_env*)env_lst->content;
		tmp = new_env->vlm;
		if (!(ret = ft_strdup(++tmp)))
			exit(errno);
	}
	return (ret);
}
