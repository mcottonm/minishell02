/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_tok.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 20:10:46 by mcottonm          #+#    #+#             */
/*   Updated: 2021/02/08 19:01:05 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void			sp_del(t_d_list **tks_in)
{
	struct s_token	*tk;
	t_d_list		*tmp;
	t_d_list		*tks;

	tks = *tks_in;
	while (tks && (tk = tks->content))
	{
		if (tk->t_stt == TK_COMMA)
			return ;
		if (tk->t_stt == TK_SP)
		{
			tmp = tks->next;
			if (tks == *tks_in)
			{
				if (tks->prev)
					*tks_in = tks->prev;
				else
					*tks_in = tks->next;
			}
			ft_dlstdelone(tks, del_token);
		}
		if (tks)
			tks = tks->next;
	}
}

struct s_token	*mini_tok_word(char **str)
{
	struct s_token	*n_tk;
	char			*tmp;

	if (!(n_tk = malloc(sizeof(struct s_token))))
		exit(errno);
	if ((tmp = ft_strchr(*str, ' ')))
	{
		if (!(n_tk->str = ft_substr(*str, 0, tmp - *str)))
			exit(errno);
		*str = tmp;
	}
	else
	{
		if (!(n_tk->str = ft_strdup(*str)))
			exit(errno);
		*str = 0;
	}
	n_tk->t_stt = TK_WORD;
	return (n_tk);
}

struct s_token	*mini_tok_sp(char **str)
{
	struct s_token	*n_tk;

	while (**str == ' ')
		++(*str);
	if (!(n_tk = malloc(sizeof(struct s_token))))
		exit(errno);
	if (!(n_tk->str = ft_strdup(" ")))
		exit(errno);
	n_tk->t_stt = TK_SP;
	return (n_tk);
}

void			mini_tok(char *str, t_d_list **tks)
{
	t_d_list		*new_tks;
	t_d_list		*tmp;
	struct s_token	*n_tk;

	if (!str)
		return ;
	new_tks = *tks;
	tmp = *tks;
	while (str && *str)
	{
		if (*str == ' ')
			n_tk = mini_tok_sp(&str);
		else if (*str)
			n_tk = mini_tok_word(&str);
		ft_dlstadd(&new_tks, ft_dlstnew(n_tk));
		new_tks = new_tks->next;
	}
	*tks = new_tks;
}
