/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 12:59:05 by mcottonm          #+#    #+#             */
/*   Updated: 2021/02/08 18:23:22 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mshell.h"
#include "../tokenizer.h"

void	err_exit(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	if (str)
	{
		ft_putstr_fd(str, 2);
		write(2, ": ", 2);
	}
	ft_putstr_fd(strerror(errno), 2);
	write(2, "\n", 1);
	if (!str)
		exit(errno);
}

void	put_msg(int sim)
{
	if (sim < 0)
		ft_putstr_fd("unclosed quote\n", 2);
	else if (sim <= 4)
		ft_putstr_fd("no filename\n", 2);
	else if (sim <= 34)
		ft_putstr_fd("near unexpected token `;;'\n", 2);
	else if (sim <= 64)
		ft_putstr_fd("near unexpected token `||'\n", 2);
}

int		ft_erro(int *e_stat, int sim)
{
	ft_putstr_fd("minishell: syntax error ", 2);
	put_msg(sim);
	*e_stat = 258;
	return (1);
}

int		error_check(char *line, int *e_stat)
{
	t_d_list	*lst;

	lst = tokenizer(line, e_stat);
	if (!*e_stat)
		*e_stat = syntax_check(lst, e_stat);
	del_tk_lst(lst);
	if (!*e_stat)
		return (0);
	return (1);
}

char	*er_to_str(int e_stat)
{
	char	*fred;
	char	*ret;

	if (e_stat == 256 && e_stat != 65280)
		e_stat = 1;
	else if (e_stat == 65280)
		e_stat = 127;
	else if (errno == 2)
		e_stat = 1;
	else if (errno != 10 && errno != 42 && !e_stat)
		e_stat = errno;
	fred = ft_itoa(e_stat);
	ret = ft_strjoin("?=", fred);
	free(fred);
	return (ret);
}
