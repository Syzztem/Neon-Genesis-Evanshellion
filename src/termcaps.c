/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 10:42:38 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/24 23:15:16 by root             ###   ########.fr       */
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
	if (line->cursor_pos.x > get_term_width())
	{
		line->cursor_pos.x = 0;
		if (line->cursor_pos.y < get_term_height())
			line->cursor_pos.y++;
		else
			line->start_column--;
	//	printf("here: %d\n", line->cursor_pos.y);
	}
	cap("im");
	ft_putchar(c);
	cap("ei");
}

void
	print_line(t_line *line)
{
	printf("line: %s\n", line->line);
	printf("r_cur_pos: %zu\n", line->r_cur_pos);
	printf("len: %zu\n", line->len);
	printf("start_row: %zu\n", line->start_row);
	printf("start_row: %zu\n", line->start_column);
	printf("max_len: %zu\n", line->max_len);
	printf("cursor_pos: .x=%zu .y=%zu\n", line->cursor_pos.x,
	line->cursor_pos.y);
}

void
	get_relative_pos(size_t r_pos, t_point *cursor)
{
	int		term_width;

	term_width = get_term_width();
	r_pos += ft_strlen(PROMPT);
	cursor->x = (r_pos % term_width) + 1;
	cursor->y = (r_pos / term_width) + 1;
}

int
	get_line_height(size_t len)
{
	int		term_width;
	size_t	prompt_len;

	prompt_len = ft_strlen(PROMPT);
	term_width = get_term_width();
	if (prompt_len > term_width)
		return ((len + prompt_len) / term_width);
	return ((len + prompt_len) / term_width + 1);
}

int
	get_start_column(t_line *line)
{
	int	column;

	column = (line->cursor_pos.y - get_line_height(line->r_cur_pos));
	return (-column * (column < 0) + column * (column > 0));
}

void
	clear_line(t_line *line)
{
	int		term_width;
	size_t	prompt_len;
	t_point	cursor;	

	term_width = get_term_width();
	prompt_len = ft_strlen(PROMPT);
	get_cursor(&(line->cursor_pos));
	get_relative_pos(line->r_cur_pos, &cursor);
	line->start_column = get_start_column(line);//line->cursor_pos.y - cursor.y;
	move_cursor(0, line->start_column);
	cap("cd");
	write(0, PROMPT, prompt_len);
	line->cursor_pos.x = prompt_len % term_width;
	line->cursor_pos.y = line->start_column;
}

void
	update_cursor(t_line *line)
{
	move_cursor(line->cursor_pos.x, line->cursor_pos.y);
}


/*
void	delete_char(t_line *line)
{
	char	*dst;
	char	*src;
	size_t	len;
	t_point	relative_cursor;
	
	if (line->r_cur_pos == 0)
		return ;
	src = line->line + line->r_cur_pos;
	dst = src - 1;
	len = ft_strlen(src);
	ft_memmove(dst, src, len);
	dst[len] = 0;
	line->len--;
	move_left(line);
	cap("dc");
	clear_line(line);
	write(0, line->line, line->len);
	get_relative_pos(line->r_cur_pos, &relative_cursor);
	line->cursor_pos.x += relative_cursor.x;
	line->cursor_pos.y += relative_cursor.y;
}
*/


void	delete_char(t_line *line)
{
	char	*dst;
	char	*src;
	size_t	len;
	t_point	tmp;
	
	if (line->r_cur_pos == 0)
		return ;
	//print_line(line);
	src = line->line + line->r_cur_pos;
	dst = src - 1;
	len = ft_strlen(src);
	ft_memmove(dst, src, len);
	dst[len] = 0;
	line->len--;
	move_left(line);
	clear_line(line);
	write(0, line->line, line->len);
	line->cursor_pos.x = (line->r_cur_pos + ft_strlen(PROMPT)) % get_term_width();
	line->cursor_pos.y += get_line_height(line->r_cur_pos) - 1; //(line->len + ft_strlen(PROMPT)) / get_term_width(); 
	update_cursor(line);
	//line->cursor_pos.x = (line->r_cur_pos + ft_strlen(PROMPT)) % get_term_width();
	////printf("start:%d\n", get_start_column(line));
	//line->cursor_pos.y = get_start_column(line) + get_line_height(line->len);
	//update_cursor(line);
//	printf("current_line: %s\n", line->line);
}

/*
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
*/
void	do_nothing(t_line *line)
{
	(void)line;
}
