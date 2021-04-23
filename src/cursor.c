/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 11:25:12 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/23 19:34:23 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"
  void
  print_line(t_line *line);

void	move_left(t_line *line)
{
	if (line->r_cur_pos == 0)
		return ;
	get_cursor(&(line->cursor_pos));
	//line->start_column = line->cursor_pos.y -  (line->r_cur_pos / tgetnum("co"));
	if (line->cursor_pos.x == 1)
	{
		line->cursor_pos.y -= 2;
		line->cursor_pos.x = tgetnum("co");
		line->r_cur_pos--;
		move_cursor(line->cursor_pos.x, line->cursor_pos.y);
		return;
		//printf("here\n");
	}
	else
		cap("le");
	line->r_cur_pos--;
	line->cursor_pos.x--;
//	print_line(line);
}

void	move_right(t_line *line)
{
	if (line->r_cur_pos == line->len)
		return ;
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
