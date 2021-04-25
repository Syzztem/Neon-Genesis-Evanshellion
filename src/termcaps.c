/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 10:42:38 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/25 05:52:51 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

void
	scroll_up_n(int n)
{
	while (n--)
	{
		cap("ll");
		cap("sf");
	}
}

void	insert_char(t_line *line, char c)
{
	t_point	tmp;
	if (line->len >= line->max_len - 1)
		realloc_line(line);
	ft_memmove(line->line + line->r_cur_pos + 1, line->line + line->r_cur_pos,
			(line->max_len - line->r_cur_pos) - 1);
	line->line[line->r_cur_pos] = c;
	line->r_cur_pos++;
	line->len++;
	line->cursor_pos.x++;
	if (line->cursor_pos.x == get_term_width())
	{
		line->cursor_pos.x = 0;
		if (line->cursor_pos.y < get_term_height() - 1)
			line->cursor_pos.y++;
	}
	if (((line->len + ft_strlen(PROMPT)) % (get_term_width())) == 0)
	{
		//line->cursor_pos.x = 0;
		if (get_last_column(line) > get_term_height() - 1)
		{
			line->start_column--;
			line->cursor_pos.y -= line->len != line->r_cur_pos;
		}
		if (line->cursor_pos.x)
			scroll_up_n(get_term_height() - line->cursor_pos.y - 1);
		else
			scroll_up_n(1);
		update_cursor(line);
	//	print_line(line);
	//	printf("here: %d\n", line->cursor_pos.y);
	}
	/*if (line->cursor_pos.y == get_last_column(line))
	{
		cap("im");
		ft_putchar(c);
		cap("ei");
	}
	else*/
	{
		tmp = line->cursor_pos;
		clear_line(line);
		cap("im");
		write(0, line->line, line->len);
		cap("ei");
		line->cursor_pos = tmp;
		update_cursor(line);
	}
}

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
	r_pos += ft_strlen(PROMPT);
	cursor->x = (r_pos % term_width);
	cursor->y = (r_pos / term_width);
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
	return ((len + prompt_len) / term_width);
}

int
	get_start_column(t_line *line)
{
	return (line->start_column);
	/*int	column;

	column = (line->cursor_pos.y - (get_line_height(line->r_cur_pos - 1)));
	return (-column * (column < 0) + column * (column > 0));*/
}

void
	clear_line(t_line *line)
{
	int		term_width;
	size_t	prompt_len;
	t_point	cursor;	

	term_width = get_term_width();
	prompt_len = ft_strlen(PROMPT);
	//get_cursor(&(line->cursor_pos));
	get_relative_pos(line->r_cur_pos, &cursor);
	line->start_column = get_start_column(line);
	move_cursor(0, line->start_column);
	cap("cd");
	move_cursor(0, line->start_column);
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
	line->cursor_pos.y += get_line_height(line->r_cur_pos); 
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
