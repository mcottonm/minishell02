/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:16:03 by mcottonm          #+#    #+#             */
/*   Updated: 2021/02/08 18:59:53 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mshell.h"
#include "../tokenizer.h"

static void	after_fork(t_d_list **tmp, t_d_list **tk_lst, int *e_stat)
{
	*e_stat = 0;
	errno = 0;
	if (*tmp && !(*tmp)->next)
	{
		*tk_lst = *tmp;
		while ((*tk_lst)->prev)
			*tk_lst = (*tk_lst)->prev;
	}
	if (*tmp)
		*tmp = (*tmp)->next;
}

void		instr_and_frk(char *line, t_d_list *env_lst, int *e_stat)
{
	t_d_list		*instrs;
	t_d_list		*tk_lst;
	t_d_list		*tmp;
	char			*qm;

	qm = 0;
	tk_lst = tokenizer(line, e_stat);
	tmp = tk_lst;
	while (tmp && !*e_stat)
	{
		instr_crt(&tmp, env_lst, e_stat);
		instrs = stg_two(&tmp);
		forker(instrs, env_lst, e_stat);
		if (*e_stat == 3)
			ft_putstr_fd("^\\Quit: 3\n", 2);
		del_instr_s(instrs);
		qm = er_to_str(*e_stat);
		set_env(env_lst, qm, 1);
		free(qm);
		after_fork(&tmp, &tk_lst, e_stat);
	}
	del_tk_lst(tk_lst);
}

static int	pre_line(t_d_list *env_lst, int *e_stat, char **line)
{
	int		s_in;
	char	*qm;

	errno = errno == 42 ? 0 : errno;
	if (0 > (s_in = dup(0)))
		err_exit(0);
	if (errno < 0)
	{
		errno = 0;
		line = 0;
		qm = er_to_str(*e_stat);
		set_env(env_lst, qm, 1);
		*e_stat = 0;
		free(qm);
	}
	errno = 0;
	return (s_in);
}

static void	post_line(char **line, int s_in)
{
	errno = errno == 42 ? 0 : errno;
	if (0 > dup2(s_in, 0))
		err_exit(0);
	close(s_in);
	if (*line)
		free(*line);
	*line = 0;
}

int			main(int ac, char **av, char **env)
{
	t_d_list		*env_lst;
	char			*line;
	int				e_stat;
	int				s_in;

	env_lst = init_env(ac, av, env);
	e_stat = 0;
	errno = -1;
	signal(SIGQUIT, handle_sigint_sl);
	signal(SIGINT, handle_sigint_c);
	while (true)
	{
		s_in = pre_line(env_lst, &e_stat, &line);
		multiline(&line, &e_stat, env_lst);
		if (!e_stat)
			instr_and_frk(line, env_lst, &e_stat);
		else if ((errno = -1) < 0)
			pre_line(env_lst, &e_stat, &line);
		post_line(&line, s_in);
	}
	return (0);
}
