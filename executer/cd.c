/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 20:59:30 by mcottonm          #+#    #+#             */
/*   Updated: 2021/02/08 16:30:42 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mshell.h"

void			cd_utils(const char *str)
{
	if (chdir(str) < 0)
	{
		ft_putendl_fd("No such file or directory\n", 1);
		errno = 1;
	}
}

static void		change_pwd(d_list *env, const char *dir)
{
	char		*pwd;
	char		*pwd_s;

	pwd = pwd_util();
	pwd_s = ft_strjoin(dir, pwd);
	set_env(env, pwd_s, 1);
	free(pwd_s);
	free(pwd);
}

void			ft_cd(char **argv, d_list *env)
{
	char		*home;

	if (argv[3])
	{
		ft_putendl_fd("No such file or directory", 1);
		errno = 1;
	}
	change_pwd(env, "OLDPWD=");
	if (!argv[1])
	{
		home = env_vlm(env, "HOME");
		if (!home)
		{
			ft_putendl_fd("HOME is unset", 1);
			errno = 1;
		}
		else
			chdir(home);
		free(home);
	}
	else if (argv[1])
		cd_utils(argv[1]);
	change_pwd(env, "PWD=");
}
