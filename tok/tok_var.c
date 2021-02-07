/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 21:39:20 by mcottonm          #+#    #+#             */
/*   Updated: 2021/02/05 20:30:35 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

bool	flt_var(const struct s_fsm_stt *stt)
{
	return (stt->in_str[stt->i] == 36 && stt->c_stt != SQ);
}

bool	flt_var_end(const struct s_fsm_stt *stt)
{
	const bool v = (ft_isalnum(stt->in_str[stt->i]));
	const bool st = (stt->c_stt == VAR || stt->c_stt == DVAR);

	return (!v && st && stt->in_str[stt->i]
	!= '_' && stt->in_str[stt->i] != '?');
}

void	hndl_var(struct s_fsm_stt *stt)
{
	g_fncs[stt->c_stt](stt);
	stt->st = ++stt->i;
	stt->c_stt = stt->c_stt == DQ ? DVAR : VAR;
}

void	hndl_var_end(struct s_fsm_stt *stt)
{
	g_fncs[stt->c_stt](stt);
	stt->st = stt->i;
	stt->c_stt = stt->c_stt == VAR ? NONE : DQ;
}

void	add_var(struct s_fsm_stt *stt)
{
	enum e_token	tmp;

	tmp = stt->c_stt == DVAR ? TK_DVAR : TK_VAR;
	tk_init(stt, tmp);
}
