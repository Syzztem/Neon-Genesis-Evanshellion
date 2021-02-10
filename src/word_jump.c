/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_jump.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 16:50:49 by lothieve          #+#    #+#             */
/*   Updated: 2021/02/09 17:09:33 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

void	prev_word(t_line *line)
{
	size_t pos;

	pos = line->r_cur_pos;
	while (*line->line && !ft_isalnum(line->line[pos]) && pos > 0)
		pos--;
	while (ft_isalnum(line->line[pos]) && pos > 0)
		pos--;
	line->cursor_pos.x = line->start_row + pos;
	line->r_cur_pos = pos;
	move_cursor(line->cursor_pos.x, line->cursor_pos.y);
}

void	next_word(t_line *line)
{
	size_t pos;

	pos = line->r_cur_pos;
	while (ft_isalnum(line->line[pos]) && pos < line->len)
		pos++;
	while (*line->line && !ft_isalnum(line->line[pos]) && pos < line->len)
		pos++;
	line->cursor_pos.x = line->start_row + pos;
	line->r_cur_pos = pos;
	move_cursor(line->cursor_pos.x, line->cursor_pos.y);
}
