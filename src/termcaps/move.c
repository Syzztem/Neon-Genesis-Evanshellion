/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 21:53:44 by user42            #+#    #+#             */
/*   Updated: 2021/04/30 20:22:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

void
	move_up(t_line *line)
{
	t_point	relative_cursor;

	get_relative_pos(line->r_cur_pos, &relative_cursor);
	if (relative_cursor.y < 1)
		return ;
	relative_cursor.y--;
	if (relative_cursor.y < 1
	&& line->cursor_pos.x < ft_strlen(prompt()) % get_term_width())
	{
		go_home(line);
		return ;
	}
	line->cursor_pos.y--;
	line->r_cur_pos = (relative_cursor.y * get_term_width())
	- ft_strlen(prompt()) + line->cursor_pos.x;
	update_cursor(line);
}

void
	move_down(t_line *line)
{
	t_point	relative_cursor;

	get_relative_pos(line->r_cur_pos, &relative_cursor);
	if (relative_cursor.y >= get_line_height(line->len))
		return ;
	if (line->cursor_pos.x > (line->len + ft_strlen(prompt()))
	% get_term_width())
	{
	
		go_end(line);
		return ;
	}
	line->cursor_pos.y++;
	relative_cursor.y++;
	line->r_cur_pos = (relative_cursor.y * (get_term_width() - 1))
	- ft_strlen(prompt()) + line->cursor_pos.x;
	update_cursor(line);
}

void
	move_left(t_line *line)
{
	if (line->r_cur_pos == 0)
		return ;
	if (line->cursor_pos.x == 0)
	{
		line->cursor_pos.y--;
		line->cursor_pos.x = get_term_width();
		line->r_cur_pos--;
		move_cursor(line->cursor_pos.x, line->cursor_pos.y);
		return ;
	}
	else
		cap("le");
	line->r_cur_pos--;
	line->cursor_pos.x--;
}

void
	move_right(t_line *line)
{
	if (line->r_cur_pos == line->len)
		return ;
	if (line->cursor_pos.x == (size_t)get_term_width())
	{
		line->cursor_pos.y++;
		line->cursor_pos.x = 0;
		line->r_cur_pos++;
		move_cursor(line->cursor_pos.x, line->cursor_pos.y);
		return ;
	}
	cap("nd");
	line->r_cur_pos++;
	line->cursor_pos.x++;
}
