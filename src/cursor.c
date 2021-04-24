/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 11:25:12 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/24 23:23:36 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

void	move_left(t_line *line)
{
	if (line->r_cur_pos == 0)
		return ;
	if (line->cursor_pos.x == 0)
	{
		//print_line(line);
		line->cursor_pos.y--;
		line->cursor_pos.x = get_term_width();
		line->r_cur_pos--;
		//print_line(line);
		move_cursor(line->cursor_pos.x, line->cursor_pos.y - 1);
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
	if (line->cursor_pos.x == get_term_width())
	{
		line->cursor_pos.y++;
		line->cursor_pos.x = 0;
		line->r_cur_pos++;
		move_cursor(line->cursor_pos.x, line->cursor_pos.y - 1);
		return;
	}
	cap("nd");
	line->r_cur_pos++;
	line->cursor_pos.x++;
}

void	go_home(t_line *line)
{
	int	term_width;

	//print_line(line);
	term_width = get_term_width();
	line->cursor_pos.x = ft_strlen(PROMPT) % term_width;
	line->start_column = get_start_column(line);
	line->cursor_pos.y = line->start_column;
	update_cursor(line);
	line->r_cur_pos = 0;
	//print_line(line);
}

void	go_end(t_line *line)
{
	int		term_width;
	t_point	relative_cursor;

	term_width = get_term_width();
	get_relative_pos(line->len, &relative_cursor);
	line->cursor_pos.x = relative_cursor.x - 1;
	line->cursor_pos.y = get_start_column(line) + relative_cursor.y - 1;
	update_cursor(line);
	line->r_cur_pos = line->len;
}
