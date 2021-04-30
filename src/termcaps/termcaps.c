/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 10:42:38 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/30 15:29:46 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

void
	scroll_up_n(int n)
{
	while (n-- > 0)
	{
		cap("ll");
		cap("sf");
	}
}

void
	wrap_line(t_line *line)
{
	int	term_width;
	int	term_height;

	term_width = get_term_width();
	term_height = get_term_height();
	if (line->cursor_pos.x == (size_t)term_width)
	{
		line->cursor_pos.x = 0;
		if (line->cursor_pos.y < term_height - 1)
			line->cursor_pos.y++;
	}
	if ((line->len + ft_strlen(prompt())) % term_width == 0)
	{
		if (get_last_column(line) > term_height - 1)
		{
			line->start_column--;
			line->cursor_pos.y -= line->len != line->r_cur_pos;
		}
		if (line->cursor_pos.x)
			scroll_up_n(term_height - line->cursor_pos.y - 1);
		else
			scroll_up_n(1);
		update_cursor(line);
	}
}

void
	clear_line(t_line *line)
{
	int		term_width;
	size_t	prompt_len;
	t_point	cursor;

	term_width = get_term_width();
	prompt_len = ft_strlen(prompt());
	get_relative_pos(line->r_cur_pos, &cursor);
	line->start_column = get_start_column(line);
	move_cursor(0, line->start_column);
	cap("cd");
	move_cursor(0, line->start_column);
	write(0, prompt(), prompt_len);
	line->cursor_pos.x = prompt_len % (term_width - 1);
	line->cursor_pos.y = line->start_column;
}

void
	do_nothing(t_line *line)
{
	(void)line;
}
