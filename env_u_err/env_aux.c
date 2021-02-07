/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_aux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 12:53:27 by mcottonm          #+#    #+#             */
/*   Updated: 2021/02/07 20:31:27 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mshell.h"

void		free_env(void *tmp)
{
	t_env	*my_env;

	my_env = (t_env*)tmp;
	free(my_env->vlm);
	free(my_env->key);
	free(my_env);
}

void		set_vlm(void **lst_cont, t_env *new_env)
{
	if (new_env->vlm)
	{
		free_env(*lst_cont);
		*lst_cont = new_env;
	}
}

char		**crt_menv(d_list *env_lst)
{
	char	**menv;
	ssize_t	i;
	t_env	*env;
	d_list	*tmp;

	i = 0;
	tmp = env_lst;
	i = ft_dlst_sz(tmp);
	if (!(menv = (char**)malloc((i + 1) * sizeof(char*))))
		exit(errno);
	i = -1;
	while (tmp && (env = (t_env*)tmp->content) && -1 < ++i)
	{
		if (ft_strcmp(env->key, "?"))
		{
			if (!env->vlm && (menv[i] = ft_strdup(env->key)))
				exit(errno);
			else if (!(menv[i] = ft_strjoin(env->key, env->vlm)))
				exit(errno);
		}
		tmp = tmp->next;
	}
	menv[i] = 0;
	return (menv);
}

t_env		*loc_env(const char *new)
{
	t_env	*my_env;
	char	*eq_pntr;

	eq_pntr = ft_strchr(new, '=');
	if (!(my_env = (t_env*)malloc(sizeof(t_env))))
		exit(errno);
	if (!eq_pntr)
	{
		if (!(my_env->key = ft_strdup(new)))
			exit(errno);
		return (my_env);
	}
	if (!(my_env->key = ft_substr(new, 0, eq_pntr - new)))
		exit(errno);
	if (!(my_env->vlm = ft_strdup(eq_pntr)))
		exit(errno);
	return (my_env);
}

d_list		*init_env(int ac, char **av, char **env)
{
	d_list	*env_lst;
	t_env	*my_env;
	int		i;

	(void)ac;
	(void)av;
	i = -1;
	env_lst = 0;
	while (env[++i])
	{
		my_env = loc_env(env[i]);
		ft_dlstadd_back(&env_lst, ft_dlstnew(my_env));
	}
	ft_dlstadd_frnt(&env_lst, ft_dlstnew(loc_env("$?=0")));
	return (env_lst);
}
