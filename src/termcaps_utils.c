/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:29:58 by lothieve          #+#    #+#             */
/*   Updated: 2021/03/25 16:02:48 by lothieve         ###   ########.fr       */
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
	tputs(tstr, 1, ft_putchar);
}

void	realloc_line(t_line *line)
{
	char *cpy;

	cpy = malloc(line->max_len + BUFF_SIZE);
	ft_memmove(cpy, line->line, line->max_len + 1);
	free(line->line);
	line->line = cpy;
	line->max_len += BUFF_SIZE;
}

void	move_cursor(int x, int y)
{
	tputs(tgoto(tgetstr("cm", NULL), x, y), 1, ft_putchar);
}

int		key_is(char *key, char *cap)
{
	if (ft_strncmp(key, tgetstr(cap, NULL), ESC_LEN))
		return (0);
	return (1);
}
