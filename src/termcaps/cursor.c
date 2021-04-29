/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 11:25:12 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/29 21:55:34 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

void
	go_home(t_line *line)
{
	int	term_width;

	term_width = get_term_width();
	line->cursor_pos.x = ft_strlen(prompt()) % term_width;
	line->start_column = get_start_column(line);
	line->cursor_pos.y = line->start_column;
	update_cursor(line);
	line->r_cur_pos = 0;
}

void
	go_end(t_line *line)
{
	int		term_width;
	t_point	relative_cursor;

	term_width = get_term_width();
	get_relative_pos(line->len, &relative_cursor);
	line->cursor_pos.x = relative_cursor.x;
	line->cursor_pos.y = get_start_column(line) + relative_cursor.y;
	update_cursor(line);
	line->r_cur_pos = line->len;
}

void
	move_cursor(int x, int y)
{
	tputs(tgoto(tgetstr("cm", NULL), x, y), 1, ft_putchar);
}
