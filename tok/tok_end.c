/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_end.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 18:21:30 by mcottonm          #+#    #+#             */
/*   Updated: 2021/02/05 20:28:54 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

bool		flt_end(const struct s_fsm_stt *stt)
{
	return (stt->in_str[stt->i] == 0);
}

void		hndl_end(struct s_fsm_stt *stt)
{
	g_fncs[stt->c_stt](stt);
	stt->i += 1;
	stt->run = 0;
}
