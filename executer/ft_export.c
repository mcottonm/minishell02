/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 13:16:14 by mcottonm          #+#    #+#             */
/*   Updated: 2021/02/07 20:31:55 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mshell.h"
#include "../tokenizer.h"

void	sort(char *menv[])
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

void	export_prnt(d_list *env_lst)
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

void	on_sun(d_list *env_lst, char **avs)
{
	t_env	*env;
	d_list	*srch_lst;

	if (!(srch_lst = srch_hide_key(env_lst, avs[1])))
		set_env(env_lst, avs[1], 1);
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

void	ft_export(d_list *env_lst, char **avs, int *e_stat)
{
	char	*tmp;

	if (avs[1])
	{
		tmp = avs[1];
		while (*tmp)
		{
			if (!ft_isalnum(*tmp) && !ft_strchr(" =-", *tmp))
			{
				*e_stat = 1;
				ft_putstr_fd(avs[1], 2);
				write(2, ": not a valid identifier\n", 25);
				return ;
			}
			++tmp;
		}
		if (ft_strchr(avs[1], '='))
			set_env(env_lst, avs[1], 1);
		else
			on_sun(env_lst, avs);
	}
	else
		export_prnt(env_lst);
}
