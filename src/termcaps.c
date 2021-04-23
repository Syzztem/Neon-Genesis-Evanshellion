/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 10:42:38 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/23 18:10:29 by root             ###   ########.fr       */
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

/*
** 
**  void
**  print_line(t_line *line)
**  {
** 	printf("line: %s\n", line->line);
** 	printf("r_cur_pos: %zu\n", line->r_cur_pos);
** 	printf("len: %zu\n", line->len);
** 	printf("start_row: %zu\n", line->start_row);
** 	printf("max_len: %zu\n", line->max_len);
** 	printf("cursor_pos: .x=%zu .y=%zu\n", line->cursor_pos.x, line->cursor_pos.y);
**  }
*/


void	delete_char(t_line *line)
{
	char	*dst;
	char	*src;
	size_t	len;
	
	if (line->r_cur_pos == 0)
		return ;
	//print_line(line);
	src = line->line + line->r_cur_pos;
	dst = src - 1;
	len = ft_strlen(src);
	ft_memmove(dst, src, len);
	dst[len] = 0;
	line->r_cur_pos--;
	line->len--;
	line->cursor_pos.x--;
	cap("le");
	cap("dc");
//	printf("current_line: %s\n", line->line);
}

void	do_nothing(t_line *line)
{
	(void)line;
}
