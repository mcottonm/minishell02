/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_sp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 18:22:05 by mcottonm          #+#    #+#             */
/*   Updated: 2021/02/07 01:04:34 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

bool		flt_sp(const struct s_fsm_stt *stt)
{
	return (stt->in_str[stt->i] == ' ' &&
	(stt->c_stt != DQ && stt->c_stt != SQ));
}

void		add_sp(struct s_fsm_stt *stt)
{
	enum e_token	tmp;

	tmp = TK_SP;
	tk_init(stt, tmp);
}

void		hndl_sp(struct s_fsm_stt *stt)
{
	g_fncs[stt->c_stt](stt);
	stt->c_stt = SP;
	stt->st = stt->i;
	while (stt->in_str[stt->i] == ' ')
		stt->st = ++stt->i;
	g_fncs[stt->c_stt](stt);
	stt->c_stt = NONE;
}
