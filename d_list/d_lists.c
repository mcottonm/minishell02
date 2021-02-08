/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_lists.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 15:56:54 by mcottonm          #+#    #+#             */
/*   Updated: 2021/02/08 19:01:45 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

t_d_list	*ft_dlstnew(void *content)
{
	t_d_list	*new_elem;

	new_elem = (t_d_list*)malloc(sizeof(t_d_list));
	if (!new_elem)
		return (0);
	new_elem->content = content;
	new_elem->next = NULL;
	new_elem->prev = NULL;
	return (new_elem);
}

void		ft_dlstadd(t_d_list **lst, t_d_list *new)
{
	t_d_list *tmp;

	tmp = *lst;
	if (!tmp)
	{
		*lst = new;
		return ;
	}
	if (tmp->next)
	{
		new->next = tmp->next;
		tmp->next->prev = new;
		new->prev = tmp;
		tmp->next = new;
	}
	else
	{
		tmp->next = new;
		new->prev = tmp;
	}
}

void		ft_dlstdelone(t_d_list *tmp, void (*del)(void*))
{
	t_d_list	*lst;

	lst = tmp;
	if (!lst)
		return ;
	if (lst->next)
		lst->next->prev = lst->prev;
	if (lst->prev)
		lst->prev->next = lst->next;
	(*del)(lst->content);
	free(tmp);
}

size_t		ft_dlst_sz(t_d_list *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		++i;
	}
	return (i);
}
