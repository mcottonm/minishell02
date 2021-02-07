/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_q.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 16:56:53 by mcottonm          #+#    #+#             */
/*   Updated: 2021/02/05 20:46:14 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

bool		flt_sq(const struct s_fsm_stt *stt)
{
	return (stt->in_str[stt->i] == 39 && stt->c_stt != DQ);
}

void		hndl_sq(struct s_fsm_stt *stt)
{
	g_fncs[stt->c_stt](stt);
	stt->c_stt = stt->c_stt == SQ ? NONE : SQ;
	stt->st = ++stt->i;
}

bool		flt_dq(const struct s_fsm_stt *stt)
{
	return (stt->in_str[stt->i] == 34 && stt->c_stt != SQ);
}

void		hndl_dq(struct s_fsm_stt *stt)
{
	g_fncs[stt->c_stt](stt);
	stt->c_stt = stt->c_stt == DQ ? NONE : DQ;
	stt->st = ++stt->i;
}
