/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_rdr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 20:07:40 by mcottonm          #+#    #+#             */
/*   Updated: 2021/02/05 20:29:57 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

bool	flt_rdr(const struct s_fsm_stt *stt)
{
	const bool a = (stt->in_str[stt->i] == '<' || stt->in_str[stt->i] == '>');
	const bool b = (stt->c_stt != DQ && stt->c_stt != SQ);

	return (a && b);
}

void	hndl_rdr(struct s_fsm_stt *stt)
{
	enum e_token	tmp;

	g_fncs[stt->c_stt](stt);
	if (stt->in_str[stt->i] == '>')
	{
		if (stt->in_str[stt->i + 1] == '>')
		{
			tmp = TK_RDR_OUT_AP;
			++stt->i;
		}
		else
			tmp = TK_RDR_OUT;
	}
	else
		tmp = TK_RDR_IN;
	stt->st = ++stt->i;
	tk_init(stt, tmp);
	stt->c_stt = NONE;
}
