/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mult.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 13:18:41 by mcottonm          #+#    #+#             */
/*   Updated: 2021/02/07 17:38:11 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mshell.h"
#include "../tokenizer.h"

char	last_chr(char *line)
{
	int		i;

	if (!line)
		return (0);
	i = ft_strlen(line) - 1;
	while (i > 0 && line[i] == ' ')
		--i;
	if (i >= 0)
		return (line[i]);
	return (0);
}

int		multiline(char **line, int *e_stat, d_list *env_lst)
{
	char	*line2;
	char	*tmp;
	d_list	*env;

	env = env_lst;
	write(1, "$>", 2);
	while (-42 == get_next_line(0, line))
		;
	if (error_check(*line, e_stat))
		return (0);
	while (last_chr(*line) == '|')
	{
		write(1, ">", 1);
		while (-42 == get_next_line(0, &line2))
			;
		if (error_check(line2, e_stat))
			return (0);
		tmp = *line;
		if (!(*line = ft_strjoin(tmp, line2)))
			exit(errno);
		free(tmp);
		free(line2);
	}
	return (0);
}
