/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_intr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 13:15:01 by mcottonm          #+#    #+#             */
/*   Updated: 2021/02/08 19:04:55 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mshell.h"
#include "../tokenizer.h"

int			rdr_out(struct s_token *rdr)
{
	int	fd;

	if (rdr->t_stt & 0b10)
		if (0 > (fd = open(rdr->str, O_RDWR | O_CREAT, 0666)))
			return (-1);
	if (rdr->t_stt & 0b100)
		if (0 > (fd = open(rdr->str, O_RDWR | O_APPEND | O_CREAT, 0666)))
			return (-1);
	if (0 > (dup2(fd, 1)))
		return (-1);
	close(fd);
	return (0);
}

char		*redir(t_d_list *rdrs)
{
	struct s_token	*rdr;
	int				fd;

	while (rdrs)
	{
		rdr = rdrs->content;
		if (rdr->t_stt & 0b1)
		{
			if (0 > (fd = open(rdr->str, O_RDWR, 0666)))
				return (rdr->str);
			if (0 > (dup2(fd, 0)))
				return (rdr->str);
			close(fd);
		}
		else if (0 > rdr_out(rdr))
			return (rdr->str);
		rdrs = rdrs->next;
	}
	return (0);
}

void		cls_fds(int *fds, int num_cmd)
{
	int		i;
	int		pips;

	i = 0;
	pips = (num_cmd - 1) * 2;
	while (i < pips && pips > 1)
		close(fds[i++]);
}

static int	duper(int *fds, int pnum, int cmd_num, void *rdr)
{
	int	exc_fd;
	int	excer_fd;

	if (cmd_num > 1)
	{
		excer_fd = 0;
		if (pnum)
		{
			exc_fd = 0;
			excer_fd = pnum + (pnum - 1);
		}
		else
			exc_fd = 1;
		if (!rdr || pnum)
			if (0 > dup2(fds[excer_fd], exc_fd))
				err_exit(0);
		if (pnum && pnum < cmd_num - 1)
		{
			if (0 > dup2(fds[++excer_fd], 1))
				err_exit(0);
		}
	}
	return (0);
}

void		chld_prc(int pnum, int *fds, t_d_list *instr, t_d_list *env_lst)
{
	struct s_instrs	*s_instr;
	char			*str;
	int				e_stat;
	int				cmd_num;

	e_stat = 0;
	s_instr = instr->content;
	cmd_num = ft_dlst_sz(instr) + pnum;
	if (s_instr->rdr)
		if ((str = redir(s_instr->rdr)))
		{
			err_exit(str);
			exit(errno);
		}
	if (s_instr->avs)
	{
		duper(fds, pnum, cmd_num, s_instr->rdr);
		cls_fds(fds, cmd_num);
		e_stat = ft_exectr(instr->content, env_lst, &e_stat);
		if (errno != 42)
			ft_putstr_fd(": command not found\n", 2);
	}
	exit(e_stat);
}
