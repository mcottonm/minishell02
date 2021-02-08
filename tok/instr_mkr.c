/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_mkr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 16:00:51 by mcottonm          #+#    #+#             */
/*   Updated: 2021/02/08 18:56:18 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static void	drf_vrl(t_d_list **tmp, t_d_list *env_list)
{
	struct s_token	*tk;
	char			*c_tmp;

	tk = (*tmp)->content;
	if (tk->t_stt & 0b110000000)
	{
		c_tmp = tk->str;
		tk->str = env_vlm(env_list, tk->str);
		free(c_tmp);
		if (tk->t_stt & 0b10000000)
			mini_tok(tk->str, tmp);
		else
			tk->t_stt = TK_WORD;
	}
}

static void	unn_words(t_d_list **tks_t)
{
	struct s_token	*nxt_tk;
	struct s_token	*tk;
	t_d_list		*tmp;
	char			*s_tmp;

	tmp = *tks_t;
	if (!tmp->next)
		return ;
	tk = tmp->content;
	nxt_tk = tmp->next->content;
	s_tmp = tk->str;
	if (tk->t_stt & 0b1000001000 && nxt_tk->t_stt & 0b1000001000)
	{
		if (!(tk->str = ft_strjoin(tk->str, nxt_tk->str)) && tk->str)
			exit(errno);
		ft_dlstdelone(tmp->next, del_token);
		free(s_tmp);
		s_tmp = tk->str;
		if (!tmp->next)
			return ;
		nxt_tk = tmp->next->content;
	}
}

static int	stg_poltora(t_d_list **tmp1)
{
	struct s_token	*tk;
	t_d_list		*tmp;

	tmp = *tmp1;
	while (tmp)
	{
		tk = tmp->content;
		if (tk->t_stt == TK_COMMA)
			return (0);
		unn_words(&tmp);
		inc_fname(tmp);
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	while (tmp->prev)
		tmp = tmp->prev;
	return (1);
}

static void	stg_one(t_d_list **tks, t_d_list *env_list)
{
	t_d_list		*tmp;
	struct s_token	*tk;

	tmp = *tks;
	while (tmp)
	{
		tk = tmp->content;
		if (tk->t_stt == TK_COMMA)
			break ;
		drf_vrl(&tmp, env_list);
		inc_fname(tmp);
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	while (tmp->prev)
		tmp = tmp->prev;
	if (!stg_poltora(&tmp))
		return ;
	*tks = tmp;
}

void		instr_crt(t_d_list **tks, t_d_list *env_list, int *e_stat)
{
	stg_one(tks, env_list);
	*e_stat = 0;
}
