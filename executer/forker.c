/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:32:29 by mcottonm          #+#    #+#             */
/*   Updated: 2021/02/07 09:26:58 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mshell.h"
#include "../tokenizer.h"

int		ft_strcmp(const char *str1, const char *str2)
{
	const unsigned char	*s1 = (unsigned char*)str1;
	const unsigned char	*s2 = (unsigned char*)str2;

	while (*s1 == *s2 && *s1)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int		*op_pips(int num_pips)
{
	int		*pips;
	int		fd[2];
	int		num_fds;

	num_fds = num_pips * 2;
	if (!(pips = malloc(num_fds * sizeof(int))))
		exit(errno);
	while (num_fds--)
	{
		if (0 > (pipe(fd)))
			return (0);
		pips[num_fds] = fd[0];
		pips[--num_fds] = fd[1];
	}
	return (pips);
}

int		pps_pds(int **fds, int **pids, int cmd_num)
{
	*fds = op_pips(cmd_num - 1);
	if (errno)
	{
		ft_putstr_fd(strerror(errno), 2);
		return (1);
	}
	if (!(*pids = malloc(cmd_num * 4 + 1)))
		err_exit(0);
	return (0);
}

int		porker(d_list *instr, d_list *env_lst, int *e_stat, int cmd_num)
{
	int				*fds;
	int				*pids;
	int				pnum;

	if ((*e_stat = pps_pds(&fds, &pids, cmd_num)))
		return (*e_stat);
	pnum = 0;
	while (instr)
	{
		if (!(pids[pnum] = fork()))
			chld_prc(pnum, fds, instr, env_lst);
		if (0 > (pids[pnum++]))
			break ;
		instr = instr->next;
	}
	cls_fds(fds, cmd_num);
	while (0 < wait(e_stat))
		;
	free(fds);
	free(pids);
	return (0);
}

int		forker(d_list *instr, d_list *env_lst, int *e_stat)
{
	int				cmd_num;
	d_list			*tmp;
	const int		stdin_cp = dup(0);
	const int		stdout_cp = dup(1);

	if (stdin_cp < 0 || stdout_cp < 0)
	{
		*e_stat = 1;
		return (0);
	}
	tmp = instr;
	cmd_num = 0;
	while (tmp && ++cmd_num)
		tmp = tmp->next;
	if (cmd_num == 1)
		*e_stat = ft_exc_one(instr->content, env_lst, e_stat);
	else
		porker(instr, env_lst, e_stat, cmd_num);
	if (0 > dup2(stdin_cp, 0) || 0 > dup2(stdout_cp, 1))
		exit(errno);
	close(stdin_cp);
	close(stdout_cp);
	return (0);
}
