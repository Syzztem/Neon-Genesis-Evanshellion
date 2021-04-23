/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 11:25:12 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/23 21:29:13 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

void	move_left(t_line *line)
{
	if (line->r_cur_pos == 0)
		return ;
	get_cursor(&(line->cursor_pos));
	if (line->cursor_pos.x == 1)
	{
		line->cursor_pos.y -= 2;
		line->cursor_pos.x = get_term_width();
		line->r_cur_pos--;
		move_cursor(line->cursor_pos.x, line->cursor_pos.y);
		return;
	}
	else
		cap("le");
	line->r_cur_pos--;
	line->cursor_pos.x--;
}

void	move_right(t_line *line)
{
	if (line->r_cur_pos == line->len)
		return ;
	get_cursor(&(line->cursor_pos));
	if (line->cursor_pos.x == get_term_width())
	{
		line->cursor_pos.y += 2;
		line->cursor_pos.x = 0;
		line->r_cur_pos++;
		move_cursor(line->cursor_pos.x, line->cursor_pos.y);
		return;
	}
	cap("nd");
	line->r_cur_pos++;
	line->cursor_pos.x++;
}

void	go_home(t_line *line)
{
	move_cursor(line->start_row, line->cursor_pos.y);
	line->r_cur_pos = 0;
	line->cursor_pos.x = line->start_row;
}

void	go_end(t_line *line)
{
	move_cursor(line->start_row + line->len, line->cursor_pos.y);
	line->r_cur_pos = line->len;
	line->cursor_pos.x = line->start_row + line->len;
}
