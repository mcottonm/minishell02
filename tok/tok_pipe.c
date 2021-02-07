/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 16:45:54 by mcottonm          #+#    #+#             */
/*   Updated: 2021/02/05 20:29:04 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

bool		flt_p(const struct s_fsm_stt *stt)
{
	return (stt->in_str[stt->i] == '|' && stt->c_stt != DQ && stt->c_stt != SQ);
}

void		add_p(struct s_fsm_stt *stt)
{
	enum e_token	tmp;

	tmp = TK_PIPE;
	tk_init(stt, tmp);
}

void		hndl_p(struct s_fsm_stt *stt)
{
	g_fncs[stt->c_stt](stt);
	stt->c_stt = PIPE;
	stt->st = stt->i;
	g_fncs[stt->c_stt](stt);
	stt->st = ++stt->i;
	stt->c_stt = NONE;
}
