/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 16:29:27 by mcottonm          #+#    #+#             */
/*   Updated: 2021/02/05 20:30:44 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void		add_w(struct s_fsm_stt *stt)
{
	enum e_token	tmp;

	tmp = TK_WORD;
	tk_init(stt, tmp);
}

bool		flt_w(const struct s_fsm_stt *stt)
{
	return (stt->c_stt == NONE);
}

void		hndl_w(struct s_fsm_stt *stt)
{
	stt->c_stt = W;
}
