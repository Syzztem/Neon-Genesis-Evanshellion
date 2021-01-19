/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:29:58 by lothieve          #+#    #+#             */
/*   Updated: 2021/01/19 13:12:51 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

int		ft_putchar(int c)
{
	return (write(1, &c, 1));
}

void	cap(char *tc)
{
	char *tstr;


	tstr = tgetstr(tc, NULL);
	if (!tstr) puts("no hay");
	tputs(tstr, 1, ft_putchar);
}

void	realloc_line(t_line *line)
{
	ft_putstr_fd("realloc", 1);
	char *cpy;

	cpy = malloc(line->max_len + BUFF_SIZE);
	ft_memmove(cpy, line->line, line->max_len);
	free(line->line);
	line->line = cpy;
	line->max_len += BUFF_SIZE;
}
