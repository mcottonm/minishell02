/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deleter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 12:51:27 by mcottonm          #+#    #+#             */
/*   Updated: 2021/02/07 10:47:37 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mshell.h"
#include "../tokenizer.h"

void	del_token(void *a)
{
	struct s_token	*tk;

	tk = (struct s_token*)a;
	if (tk->str)
		free(tk->str);
	free(tk);
}

char	*free_srch(t_srch *srch)
{
	char	*ret;

	if (errno)
	{
		errno = 0;
		ret = 0;
		free(srch->prog);
	}
	else
		ret = srch->prog;
	free(srch->path);
	free(srch->name);
	free(srch);
	return (ret);
}

void	del_instr(void *content)
{
	struct s_instrs	*instr;
	int				i;
	d_list			*tmp;

	instr = content;
	i = -1;
	while (instr->avs && instr->avs[++i])
		free(instr->avs[i]);
	free(instr->avs);
	tmp = instr->rdr;
	while (tmp)
	{
		instr->rdr = tmp;
		tmp = tmp->next;
		ft_dlstdelone(instr->rdr, del_token);
	}
	free(content);
}

void	del_instr_s(void *instrs)
{
	d_list	*tmp1;
	d_list	*tmp2;

	tmp1 = instrs;
	while (tmp1)
	{
		tmp2 = tmp1;
		tmp1 = tmp1->next;
		ft_dlstdelone(tmp2, del_instr);
	}
}

void	del_tk_lst(d_list *tk_lst)
{
	d_list *tmp;

	tmp = tk_lst;
	while (tmp)
	{
		tk_lst = tmp;
		tmp = tmp->next;
		ft_dlstdelone(tk_lst, del_token);
	}
}
