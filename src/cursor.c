/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 11:25:12 by lothieve          #+#    #+#             */
/*   Updated: 2021/01/20 10:43:23 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

void	move_left(t_line *line)
{
	if (line->r_cur_pos == 0)
		return ;
	cap("le");
	line->r_cur_pos--;
	line->cursor_pos.x--;
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
