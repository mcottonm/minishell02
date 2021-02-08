/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explorer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 13:05:32 by mcottonm          #+#    #+#             */
/*   Updated: 2021/02/08 18:51:19 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mshell.h"
#include "../tokenizer.h"

static char		*next_dir(char *path, char *name)
{
	char	*ret;
	char	*ret2;

	if (ft_strchr(path, ':'))
	{
		if (!(ret = ft_substr(path, 0, ft_strchr(path, ':') - path)))
			exit(errno);
	}
	else
	{
		if (!(ret = ft_strdup(path)))
			exit(errno);
	}
	if (!(ret2 = ft_strjoin(ret, name)))
		exit(errno);
	free(ret);
	return (ret2);
}

static t_srch	*init_srch(char **avs, t_d_list *env_lst)
{
	t_srch			*srch;

	srch = malloc(sizeof(t_srch));
	if (!(srch->path = env_vlm(env_lst, "PATH")))
		return (0);
	srch->tmp = srch->path;
	if (!(srch->name = ft_strjoin("/", avs[0])))
		exit(errno);
	if (!(srch->prog = malloc(1)))
		exit(errno);
	srch->prog[0] = 0;
	return (srch);
}

char			*srch_prgm(char **avs, t_d_list *env_lst)
{
	struct stat		buf;
	t_srch			*srch;
	char			*ret;

	if (!(srch = init_srch(avs, env_lst)))
		return (0);
	while (lstat(srch->prog, &buf))
	{
		free(srch->prog);
		srch->prog = next_dir(srch->tmp, srch->name);
		if (!(ft_strchr(srch->tmp, ':')))
			break ;
		else
			srch->tmp = ft_strchr(srch->tmp, ':') + 1;
	}
	errno = 0;
	if (lstat(srch->prog, &buf))
		return (free_srch(srch));
	ret = free_srch(srch);
	return (ret);
}
