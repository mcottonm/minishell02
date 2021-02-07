/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 17:09:58 by mcottonm          #+#    #+#             */
/*   Updated: 2021/02/07 17:59:58 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mshell.h"

static int				in_line(t_string *buf, t_string *nline, size_t aplen)
{
	size_t	nnlen;
	char	*nlstr;

	nnlen = nline->slen + aplen;
	nlstr = malloc(nnlen + 1);
	if (!nlstr)
		exit(errno);
	ft_memcpy(nlstr, nline->str, nline->slen);
	ft_memcpy(nlstr + nline->slen, buf->str, aplen);
	nlstr[nnlen] = '\0';
	free(nline->str);
	nline->str = nlstr;
	nline->slen = nnlen;
	return (0);
}

static int				joi(t_string *buf, t_string *nline)
{
	char	*reline;
	char	*dline;
	size_t	aplen;
	size_t	remlen;

	reline = ft_memchr(buf->str, '\n', buf->slen);
	dline = reline ? reline : buf->str + buf->slen;
	aplen = dline - buf->str;
	remlen = buf->slen - aplen - (reline != 0);
	if (in_line(buf, nline, aplen) == -1)
		return (-1);
	if (reline)
		ft_memcpy(buf->str, reline + 1, remlen);
	buf->slen = remlen;
	return (reline == 0);
}

static inline t_string	*get_buff(int fd)
{
	static t_string		buff[FD_MAX];

	if (fd < 0 || fd >= FD_MAX || BUFFER_SIZE <= 0)
		return (0);
	if (!(buff[fd].str))
	{
		if (!(buff[fd].str = malloc(BUFFER_SIZE + 1)))
			exit(errno);
		buff[fd].slen = 0;
		buff[fd].str[0] = '\0';
	}
	return (&buff[fd]);
}

static inline int		crt_line(t_string *nline)
{
	nline->str = malloc(1);
	if (!(nline->str))
		exit(errno);
	nline->str[0] = '\0';
	nline->slen = 0;
	return (0);
}

int						get_next_line(int fd, char **line)
{
	t_string *const		buff = get_buff(fd);
	t_string			nline;
	ssize_t				rl[2];
	int					flag;

	if (!buff || crt_line(&nline) < 0)
		return (-1);
	rl[0] = joi(buff, &nline);
	flag = 0;
	while (flag >= 0 && rl[0] > 0 &&
	(rl[1] = read(fd, buff->str, BUFFER_SIZE)) >= 0)
	{
		if (!rl[1] && buff->str[0] == '\n')
			flag = -2;
		buff->slen = rl[1];
		buff->str[rl[1]] = '\0';
		rl[0] = joi(buff, &nline);
		if (!flag++ && !rl[1])
		{
			ft_putstr_fd("exit\n", 0);
			exit(0);
		}
	}
	after_prty(rl, &nline, line, buff);
	return (rl[0]);
}
