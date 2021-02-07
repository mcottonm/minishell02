/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 13:13:19 by mcottonm          #+#    #+#             */
/*   Updated: 2021/02/07 14:16:42 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mshell.h"
#include "../tokenizer.h"

int		ft_exectr(void *instr_in, d_list *env_lst, int *e_stat)
{
	char			**menv;
	char			*way;
	struct s_instrs	*instr;

	instr = instr_in;
	if ((ft_strchr(instr->avs[0], '=')) && instr->avs[1])
	{
		set_env(env_lst, instr->avs[0], 0);
		++instr->avs;
	}
	if (!bin_fltr(instr->avs, env_lst, 0))
	{
		errno = 42;
		return (0);
	}
	if (!ft_strchr(instr->avs[0], '/'))
		way = srch_prgm(instr->avs, env_lst);
	else
		way = instr->avs[0];
	menv = crt_menv(env_lst);
	*e_stat = execve(way, instr->avs, menv);
	ft_putstr_fd(instr->avs[0], 2);
	return (*e_stat);
}

char	*pre_proc(char ***avs, d_list *env_lst, char ***menv, int *e_stat)
{
	char			*way;

	if (!*avs)
		return (0);
	if (ft_strchr((*avs)[0], '='))
	{
		set_env(env_lst, (*avs)[0], 0);
		if (!(*avs)[1] && (errno = 42))
			return (0);
		++(*avs);
	}
	if ((!bin_fltr(*avs, env_lst, e_stat)))
	{
		errno = 42;
		return (0);
	}
	if (!ft_strchr((*avs)[0], '/'))
		way = srch_prgm(*avs, env_lst);
	if (ft_strchr((*avs)[0], '/') || !way)
		way = ft_strdup((*avs)[0]);
	*menv = crt_menv(env_lst);
	return (way);
}

void	post_proc(char ***avs, char *way, char **menv, char **tmp)
{
	if (errno != 42)
	{
		*avs = tmp;
		if (way)
			free(way);
		tmp = menv;
		while (menv && *menv)
			free(*(menv++));
		free(tmp);
	}
}

void	frk_exit(char *str, int *e_stat)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(*e_stat);
}

int		ft_exc_one(void *instr_in, d_list *env_lst, int *e_stat)
{
	char			**menv;
	char			**tmp;
	char			*way;
	struct s_instrs	*instr;

	if ((instr = instr_in) && instr->rdr)
		if (0 != (way = redir(instr->rdr)))
		{
			err_exit(way);
			return (errno);
		}
	tmp = instr->avs;
	if (!(way = pre_proc(&instr->avs, env_lst, &menv, e_stat)) && errno != 42)
		return (0);
	if (errno != 42 && !fork())
	{
		*e_stat = execve(way, instr->avs, menv);
		frk_exit(instr->avs[0], e_stat);
	}
	if (errno != 42)
		wait(e_stat);
	post_proc(&instr->avs, way, menv, tmp);
	return (*e_stat);
}
