/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stg_two.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 17:11:59 by mcottonm          #+#    #+#             */
/*   Updated: 2021/02/07 19:14:01 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void			inc_fname(d_list *tks)
{
	struct s_token	*nxt_tk;
	struct s_token	*tk;

	tk = tks->content;
	if (!tks->next)
		return ;
	nxt_tk = tks->next->content;
	if (nxt_tk->t_stt == TK_SP)
	{
		if (!tks->next->next)
			return ;
		nxt_tk = tks->next->next->content;
	}
	if (tk->t_stt & 0b111 && nxt_tk->t_stt == TK_WORD)
		nxt_tk->t_stt = TK_FNAME;
}

char			**add_av(char **avs, char *str)
{
	int		i;
	char	**new;

	if (!avs && !str)
		return (0);
	i = 0;
	while (avs && avs[i])
		++i;
	i = i == 0 ? 1 : i;
	if (!(new = (char**)calloc((i + 2),  sizeof(char*))))
		exit(errno);
	i = -1;
	while (avs && avs[++i])
		new[i] = avs[i];
	i = i == -1 ? 0 : i;
	if (!str)
		new[i] = 0;
	else if (!(new[i] = ft_strdup(str)))
		exit(errno);
	new[++i] = 0;
	free(avs);
	return (new);
}

void			add_rdr(d_list *tks, d_list **rdr)
{
	struct s_token	*rdr_vl;
	struct s_token	*tk;

	if (!(rdr_vl = malloc(sizeof(struct s_token))))
		exit(errno);
	tk = tks->content;
	rdr_vl->t_stt = tk->t_stt;
	tk = tks->next->content;
	if (tk->t_stt == TK_SP)
	{
		if (!tks->next->next)
			return ;
		tk = tks->next->next->content;
	}
	if (!(rdr_vl->str = ft_strdup(tk->str)))
		exit(errno);
	ft_dlstadd_back(rdr, ft_dlstnew(rdr_vl));
}

struct s_instrs	*init_instr(void)
{
	struct s_instrs	*instr;

	if (!(instr = malloc(sizeof(struct s_instrs))))
		exit(errno);
	instr->avs = 0;
	instr->rdr = 0;
	instr->type = CMD;
	return (instr);
}

d_list			*stg_two(d_list **tks)
{
	d_list			*instrs;
	struct s_instrs	*instr;
	struct s_token	*tk;

	instrs = 0;
	instr = init_instr();
	while (*tks && (tk = (*tks)->content))
	{
		if (tk->t_stt & 0b1100000)
		{
			ft_dlstadd_back(&instrs, ft_dlstnew(instr));
			if (tk->t_stt == TK_COMMA)
				return (instrs);
			instr = init_instr();
		}
		else if (tk->t_stt == TK_WORD)
			instr->avs = (add_av(instr->avs, tk->str));
		else if (tk->t_stt & 0b111)
			add_rdr(*tks, &instr->rdr);
		if (!(*tks)->next)
			break ;
		*tks = (*tks)->next;
	}
	ft_dlstadd_back(&instrs, ft_dlstnew(instr));
	return (instrs);
}
