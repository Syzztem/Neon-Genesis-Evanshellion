/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 10:42:38 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/03 16:23:07 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

void	insert_char(t_line *line, char c)
{
	if (line->len >= line->max_len - 1)
		realloc_line(line);
	ft_memmove(line->line + line->r_cur_pos + 1, line->line + line->r_cur_pos,
			(line->max_len - line->r_cur_pos) - 1);
	line->line[line->r_cur_pos] = c;
	line->r_cur_pos++;
	line->len++;
	line->cursor_pos.x++;
	cap("im");
	ft_putchar(c);
	cap("ei");
}

void	delete_char(t_line *line)
{
	if (line->r_cur_pos == 0)
		return ;
	ft_memmove(line->line + line->r_cur_pos - 1, line->line + line->r_cur_pos,
			(line->max_len - line->r_cur_pos));
	line->r_cur_pos--;
	line->len--;
	line->cursor_pos.x--;
	cap("le");
	cap("dc");
}

void	do_nothing(t_line *line)
{
	(void)line;
}
