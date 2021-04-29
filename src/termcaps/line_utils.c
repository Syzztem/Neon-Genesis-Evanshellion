/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 21:44:03 by user42            #+#    #+#             */
/*   Updated: 2021/04/29 21:58:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

void
	print_line(t_line *line)
{
	printf("line: %s\n", line->line);
	printf("r_cur_pos: %zu\n", line->r_cur_pos);
	printf("len: %zu\n", line->len);
	printf("start_row: %zu\n", line->start_row);
	printf("start_col: %zu\n", line->start_column);
	printf("max_len: %zu\n", line->max_len);
	printf("cursor_pos: .x=%zu .y=%zu\n", line->cursor_pos.x,
	line->cursor_pos.y);
}

void
	get_relative_pos(size_t r_pos, t_point *cursor)
{
	int		term_width;

	term_width = get_term_width();
	r_pos += ft_strlen(prompt());
	cursor->x = (r_pos % term_width);
	cursor->y = (r_pos / term_width);
}

int
	get_line_height(size_t len)
{
	int		term_width;
	size_t	prompt_len;

	prompt_len = ft_strlen(prompt());
	term_width = get_term_width();
	if (prompt_len > (size_t)term_width)
		return ((len + prompt_len) / term_width);
	return ((len + prompt_len) / term_width);
}

int
	get_start_column(t_line *line)
{
	return (line->start_column);
}

int
	get_last_column(t_line *line)
{
	t_point	relative_cursor;

	get_relative_pos(line->len, &relative_cursor);
	return (get_start_column(line) + relative_cursor.y);
}
