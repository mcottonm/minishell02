/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bins.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 13:03:28 by mcottonm          #+#    #+#             */
/*   Updated: 2021/02/08 18:23:49 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mshell.h"
#include "../tokenizer.h"

static char	exit_atoi(char *str)
{
	int			i;
	char		at;
	char		p;

	i = 1;
	at = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-')
		i = -1;
	if ((*str == '+') || (*str == '-'))
		str++;
	while (*str >= '0' && *str <= '9')
	{
		p = at;
		at = at * 10 - '0' + *str++;
	}
	return (at * i);
}

static int	exit_er(char **avs, bool *flag)
{
	int i;

	i = -1;
	while (avs[1] && avs[1][++i])
	{
		if (!ft_isdigit(avs[1][i]) && (*flag = true))
		{
			*flag = true;
			ft_putstr_fd("exit: numeric argument required\n", 2);
			return (255);
			break ;
		}
	}
	if (avs[1] && avs[2] && flag)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (0);
	}
	return (1);
}

static void	ft_exit(char **avs, t_d_list *env_lst)
{
	bool			flag;
	unsigned char	ret;
	char			*err;

	flag = false;
	ft_putstr_fd("exit\n", 1);
	ret = exit_er(avs, &flag);
	if (!ret)
		return ;
	if (ret == 255)
		exit(ret);
	if (!avs[1])
	{
		err = env_vlm(env_lst, "?");
		ret = exit_atoi(err);
	}
	else
		ret = errno && !exit_atoi(avs[1]) ? errno : exit_atoi(avs[1]);
	exit(ret);
}

static int	bin_fltr2(const char *bin, char **avs, int i, t_d_list *env_lst)
{
	int e_stat;

	e_stat = 0;
	if (!ft_strcmp(bin, avs[0]))
	{
		if (i == 0)
			ft_export(env_lst, avs, &e_stat);
		if (i == 1)
			unset_env(env_lst, avs[1]);
		if (i == 2)
			ft_env(env_lst);
		if (i == 3)
			ft_exit(avs, env_lst);
		if (i == 4)
			ft_echo(avs);
		if (i == 5)
			ft_cd(avs, env_lst);
		if (i == 6)
			ft_pwd();
		return (-1);
	}
	return (e_stat);
}

bool		bin_fltr(char **avs, t_d_list *env_lst, int *e_stat)
{
	const char	*bins[] = {"export", "unset",
	"env", "exit", "echo", "cd", "pwd", 0};
	int			i;

	if (ft_strchr(avs[0], '='))
		set_env(env_lst, avs[0], 0);
	i = 0;
	while (bins[i])
	{
		if (e_stat && (*e_stat = bin_fltr2(bins[i], avs, i, env_lst)))
		{
			*e_stat = *e_stat < 0 ? 0 : *e_stat;
			return (false);
		}
		else if (!e_stat && bin_fltr2(bins[i], avs, i, env_lst))
			return (false);
		++i;
	}
	return (true);
}
