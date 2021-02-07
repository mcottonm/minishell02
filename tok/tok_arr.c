/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_arr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 11:15:01 by jiandre           #+#    #+#             */
/*   Updated: 2021/02/05 20:35:10 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

t_fltr g_flts[FSM_N] = {
	flt_var_end,
	flt_sp,
	flt_com,
	flt_p,
	flt_sq,
	flt_dq,
	flt_end,
	flt_var,
	flt_rdr,
	flt_w,
};

t_hndl g_hndls[FSM_N] = {
	hndl_var_end,
	hndl_sp,
	hndl_com,
	hndl_p,
	hndl_sq,
	hndl_dq,
	hndl_end,
	hndl_var,
	hndl_rdr,
	hndl_w,
};

t_fnc g_fncs[] = {
	add_n,
	add_w,
	add_sp,
	add_var,
	add_com,
	add_p,
	add_w,
	add_w,
	add_var,
};
