/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_lines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 22:00:41 by user42            #+#    #+#             */
/*   Updated: 2021/04/29 22:01:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

t_line
	*realloc_lines(t_line *hist_lines, size_t *size, t_line **current_line)
{
	t_line	*out;
	size_t	current_line_pos;

	current_line_pos = *current_line - hist_lines;
	out = ft_calloc(sizeof(t_line), *size + LINE_ALLOC_SIZE);
	ft_memmove(out, hist_lines, sizeof(t_line) * *size);
	*current_line = out + current_line_pos;
	(*size) += LINE_ALLOC_SIZE;
	free(hist_lines);
	return (out);
}

t_line
	*change_line(t_line *new, size_t current_column)
{
	t_point	relative;

	new->r_cur_pos = new->len;
	get_relative_pos(new->len, &relative);
	new->cursor_pos.x = relative.x;
	new->start_column = current_column;
	new->cursor_pos.y = new->start_column + relative.y;
	if (new->cursor_pos.y > get_term_height() - 1)
		new->start_column -= new->cursor_pos.y - (get_term_height() - 1);
	new->cursor_pos.y = new->start_column + relative.y;
	return (new);
}

t_line
	*next_line(t_line *origin, t_line *hist_lines,
			size_t *line_count, int hist_fd)
{
	hist_lines += *line_count;
	if ((hist_lines - 1) != origin)
		return (change_line(origin + 1, origin->start_column));
	if (!get_next_line(hist_fd, &hist_lines->line))
		return (origin);
	create_line(hist_lines, origin);
	(*line_count)++;
	return (hist_lines);
}

t_line
	*prev_line(t_line *hist_lines, t_line *current)
{
	if (current == hist_lines)
		return (current);
	return (change_line(current - 1, current->start_column));
}
