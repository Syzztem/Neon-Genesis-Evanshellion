/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 21:45:29 by user42            #+#    #+#             */
/*   Updated: 2021/04/29 21:47:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

void
	delete_char(t_line *line)
{
	char	*dst;
	char	*src;
	size_t	len;

	if (line->r_cur_pos == 0)
		return ;
	src = line->line + line->r_cur_pos;
	dst = src - 1;
	len = ft_strlen(src);
	ft_memmove(dst, src, len);
	dst[len] = 0;
	line->len--;
	move_left(line);
	clear_line(line);
	write(0, line->line, line->len);
	line->cursor_pos.x = (line->r_cur_pos + ft_strlen(prompt()))
						% get_term_width();
	line->cursor_pos.y += get_line_height(line->r_cur_pos);
	update_cursor(line);
}
