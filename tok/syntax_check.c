/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 04:40:35 by mcottonm          #+#    #+#             */
/*   Updated: 2021/02/07 15:00:28 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

struct s_token *sp_check(d_list *tks)
{
	struct s_token *next_tk;

	next_tk = tks->next->content;
	if (next_tk->t_stt == TK_SP)
	{
		if (tks->next->next)
			return (tks->next->next->content);
		else
			return (0);
	}
	return (next_tk);
}

static bool check_next(d_list *tks)
{
	struct s_token *next_tk;
	struct s_token *tk;

	if (!tks->next)
		return (0);
	tk = tks->content;
	if (tk->t_stt & 0b1000000)
		return (1);
	if (!(next_tk = sp_check(tks)))
		return (0);
	if (tk->t_stt & 0b111 && next_tk->t_stt & 0b111)
		return (0);
	if (!(next_tk->t_stt & 0b1000001111))
		return (0);
	return (1);
}

static bool check_prev(d_list *tks)
{
	struct s_token *prev_tk;

	if (!tks->prev)
		return (0);
	prev_tk = tks->prev->content;
	if (prev_tk->t_stt == TK_SP)
	{
		if (tks->prev->prev)
			prev_tk = tks->prev->prev->content;
		else
			return (0);
	}
	if (!(prev_tk->t_stt & 0b1110001000))
		return (0);
	return (1);
}

int syntax_check(d_list *tks, int *e_stat)
{
	struct s_token *tk;

	while (tks)
	{
		tk = tks->content;
		if (tk->t_stt & 0b1100111)
		{
			if ((!*e_stat || tk->t_stt & 0b111) && tk->t_stt != TK_COMMA && !check_next(tks))
			{
				ft_erro(e_stat, tk->t_stt);
				return (258);
			}
			if (!check_prev(tks) && !(tk->t_stt & 0b111))
			{
				ft_erro(e_stat, tk->t_stt);
				return (258);
			}
		}
		tks = tks->next;
	}
	return (0);
}
