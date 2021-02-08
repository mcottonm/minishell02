/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_list_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 16:45:38 by mcottonm          #+#    #+#             */
/*   Updated: 2021/02/08 18:31:46 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

void	ft_dlstadd_back(t_d_list **lst, t_d_list *new)
{
	t_d_list *tmp;

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

void	ft_dlstadd_frnt(t_d_list **lst, t_d_list *new)
{
	t_d_list *tmp;

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

void	ft_dlstadd_lst(t_d_list **lst, t_d_list *new)
{
	t_d_list	*tmp;
	t_d_list	*new_end;

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
