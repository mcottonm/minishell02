/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_lists.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 15:56:54 by mcottonm          #+#    #+#             */
/*   Updated: 2021/01/28 13:42:22 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

d_list	*ft_dlstnew(void *content)
{
	d_list	*new_elem;

	new_elem = (d_list*)malloc(sizeof(d_list));
	if (!new_elem)
		return (0);
	new_elem->content = content;
	new_elem->next = NULL;
	new_elem->prev = NULL;
	return (new_elem);
}

void	ft_dlstadd(d_list **lst, d_list *new)
{
	d_list *tmp;

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

void	ft_dlstdelone(d_list *tmp, void (*del)(void*))
{
	d_list	*lst;

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

void	ft_dlstadd_back(d_list **lst, d_list *new)
{
	d_list *tmp;

	tmp = *lst;
	if (!tmp)
	{
		*lst = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	new->next = 0;
}

void	ft_dlstadd_frnt(d_list **lst, d_list *new)
{
	d_list *tmp;

	tmp = *lst;
	if (!tmp)
	{
		*lst = new;
		return ;
	}
	while (tmp->prev)
		tmp = tmp->prev;
	tmp->prev = new;
	new->next = tmp;
}

void	ft_dlstadd_lst(d_list **lst, d_list *new)
{
	d_list	*tmp;
	d_list	*new_end;

	tmp = *lst;
	if (!tmp)
		*lst = new;
	else if (tmp->next)
	{
		new_end = new;
		while (new_end->next)
			new_end = new_end->next;
		new_end->next = tmp->next;
		tmp->next->prev = new_end;
		new->prev = tmp;
		tmp->next = new;
	}
	else
	{
		tmp->next = new;
		new->prev = tmp;
	}
}

size_t	ft_dlst_sz(d_list *lst)
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
