/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 18:19:20 by mcottonm          #+#    #+#             */
/*   Updated: 2021/02/07 05:21:24 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void					tk_init(struct s_fsm_stt *stt, enum e_token tmp)
{
	struct s_token *tk;

	if (!(tk = malloc(sizeof(struct s_token))))
		exit(errno);
	tk->t_stt = tmp;
	if (!(tk->str = ft_substr(stt->in_str, stt->st, stt->i - stt->st)))
		exit(errno);
	ft_dlstadd_back(&stt->tk_list, ft_dlstnew(tk));
}

void					add_n(struct s_fsm_stt *stt)
{
	(void)stt;
}

static void				stt_init(struct s_fsm_stt *stt, char *cmd)
{
	stt->c_stt = NONE;
	stt->in_str = cmd;
	stt->st = 0;
	stt->i = stt->st;
	stt->run = true;
	stt->tk_list = NULL;
}

d_list					*tokenizer(char *cmd, int *e_stat)
{
	struct s_fsm_stt	stt;
	int					f_idx;

	stt_init(&stt, cmd);
	while (stt.run == true && cmd)
	{
		f_idx = 0;
		while (f_idx < FSM_N)
		{
			if (g_flts[f_idx](&stt) == true)
			{
				g_hndls[f_idx](&stt);
				break ;
			}
			f_idx += 1;
		}
		if (f_idx == FSM_N)
			++stt.i;
	}
	if (stt.c_stt == SQ || stt.c_stt == DQ)
		ft_erro(e_stat, -1);
	return (stt.tk_list);
}
