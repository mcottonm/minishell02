/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maux.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 17:10:28 by mcottonm          #+#    #+#             */
/*   Updated: 2021/02/07 20:33:26 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mshell.h"

void	handle_sigint_c(int sig)
{
	(void)sig;
	close(0);
	write(1, "\b\b", 1);
	write(1, "\b\b", 1);
	write(1, " ", 1);
	write(1, " ", 1);
	write(1, "\n", 1);
}

void	handle_sigint_sl(int sig)
{
	(void)sig;
	write(1, "\b\b  \b\b", 7);
}

void	free_buff(t_string *buf)
{
	free(buf->str);
	buf->slen = 0;
	buf->str = NULL;
}

void	after_prty(ssize_t *rl, t_string *nline,
char **line, t_string *const buff)
{
	rl[0] = rl[1] < 0 ? -1 : rl[0];
	rl[0] = rl[0] < 0 ? rl[0] : rl[1] != 0;
	if (rl[0] < 0)
		free_buff(nline);
	else
		*line = nline->str;
	free_buff(buff);
}
