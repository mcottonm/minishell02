/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_com.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:49:33 by mcottonm          #+#    #+#             */
/*   Updated: 2021/02/05 20:28:38 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

bool	flt_com(const struct s_fsm_stt *stt)
{
	const bool a = (stt->in_str[stt->i] == ';' || stt->in_str[stt->i] == '\n');
	const bool b = (stt->c_stt != DQ && stt->c_stt != SQ);

	return (a && b);
}

void	hndl_com(struct s_fsm_stt *stt)
{
	g_fncs[stt->c_stt](stt);
	stt->c_stt = COMMA;
	g_fncs[stt->c_stt](stt);
	stt->st = ++stt->i;
	stt->c_stt = NONE;
}

void	add_com(struct s_fsm_stt *stt)
{
	enum e_token	tmp;

	tmp = TK_COMMA;
	tk_init(stt, tmp);
}
