/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 13:16:14 by mcottonm          #+#    #+#             */
/*   Updated: 2021/02/08 19:05:30 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mshell.h"
#include "../tokenizer.h"

static void	sort(char *menv[])
{
	int		i;
	int		j;
	int		size;
	char	*tmp;

	size = 0;
	i = 0;
	while (menv[i++])
		++size;
	i = -1;
	while (++i < size - 1)
	{
		j = size;
		while (--j > i)
		{
			if (ft_strcmp(menv[j - 1], menv[j]) > 0)
			{
				tmp = menv[j - 1];
				menv[j - 1] = menv[j];
				menv[j] = tmp;
			}
		}
	}
}

static void	export_prnt(t_d_list *env_lst)
{
	char	**tmp_m;
	int		i;

	tmp_m = crt_menv(env_lst);
	sort(tmp_m);
	i = -1;
	while (tmp_m[++i])
	{
		ft_putstr_fd("declare -x ", 1);
		if (ft_strchr(tmp_m[i], '='))
		{
			write(1, tmp_m[i], ft_strchr(tmp_m[i], '=') - tmp_m[i]);
			write(1, "=\"", 2);
			ft_putstr_fd(ft_strchr(tmp_m[i], '=') + 1, 1);
			write(1, "\"", 1);
		}
		else
			ft_putstr_fd(tmp_m[i], 1);
		write(1, "\n", 1);
		free(tmp_m[i]);
	}
	free(tmp_m);
}

static void	on_sun(t_d_list *env_lst, char *avs)
{
	t_env		*env;
	t_d_list	*srch_lst;

	if (!(srch_lst = srch_hide_key(env_lst, avs)))
		set_env(env_lst, avs, 1);
	else
	{
		env = srch_lst->content;
		if (env->vlm)
		{
			if (srch_lst->next)
				srch_lst->next->prev = srch_lst->prev;
			if (srch_lst->prev)
				srch_lst->prev->next = srch_lst->next;
			ft_dlstadd_back(&env_lst, srch_lst);
			while (env_lst)
				env_lst = env_lst->next;
		}
	}
}

void		ft_export(t_d_list *env_lst, char **avs, int *e_stat)
{
	int		c;
	int		i;

	i = 0;
	while (avs[++i])
	{
		c = -1;
		while (avs[i][++c] && avs[i][c] != '=')
		{
			if (!ft_isalnum(avs[i][c]) && !ft_strchr("-", avs[i][c]))
			{
				*e_stat = 1;
				ft_putstr_fd("minishell: export:", 2);
				ft_putstr_fd(avs[i], 2);
				write(2, ": not a valid identifier\n", 25);
				return ;
			}
		}
		if (ft_strchr(avs[i], '='))
			set_env(env_lst, avs[i], 1);
		else
			on_sun(env_lst, avs[i]);
	}
	if (!avs[1])
		export_prnt(env_lst);
}
