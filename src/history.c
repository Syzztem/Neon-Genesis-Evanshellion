/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 13:22:07 by lothieve          #+#    #+#             */
/*   Updated: 2021/01/21 14:14:37 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//remove when getenv done

void
	db_print_line(t_line *line)
{
	printf("\nline\n\t.line = %s\n\t.r_cur_pos = %zu\n\t.len = %zu\n\t.start_row = %zu\n\t.max_len = %zu\n\t.cursor_pos = %zu, %zu\n",
			line->line, line->r_cur_pos, line->len, line->start_row, line->max_len, line->cursor_pos.x, line->cursor_pos.y);
}

static char
	*ft_getenv(char *name)
{
	(void)name;
	return (NULL);
}

void
	add_to_hist(char *cmd)
{
	int		fd;
	char	*path;

	path = ft_getenv(HIST_ENV);
	if (!path)
		path = DEFAULT_HIST_FILE;
	fd = open(path, O_CREAT | O_APPEND | O_WRONLY, S_IRUSR | S_IWUSR);
	ft_putendl_fd(cmd, fd);
	close(fd);
}

static t_line
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

static t_line
	*next_line(t_line *origin, t_line *hist_lines,
			size_t *line_count, int hist_fd)
{
	hist_lines += *line_count;
	if ((hist_lines - 1) != origin)
		return (origin + 1);
	if (!get_next_line(hist_fd, &hist_lines->line))
		return (origin);
	create_line(hist_lines, origin);
	(*line_count)++;
	return (hist_lines);
}

static t_line
	*prev_line(t_line *hist_lines, t_line *current)
{
	if (current == hist_lines)
		return (current);
	return (current - 1);
}

static void
	loop_hist(t_line *line, int hist_fd)
{
	t_line	*hist_lines;
	size_t	line_count;
	size_t	hist_size;
	char	next_key[5];
	t_line	*current_line;

	hist_lines = ft_calloc(sizeof(t_line), LINE_ALLOC_SIZE);
	line_count = 1;
	*hist_lines = *line;
	hist_size = LINE_ALLOC_SIZE;
	current_line = hist_lines;
	while (1)
	{
		if (line_count == hist_size)
			hist_lines = realloc_lines(hist_lines, &hist_size, &current_line);
		if (key_is(next_key, "kd"))
			current_line = prev_line(hist_lines, current_line);
		else
			current_line = next_line(current_line, hist_lines, &line_count, hist_fd);
		set_line(current_line);
		get_key(next_key);
		if (!(key_is(next_key, "ku") || key_is(next_key, "kd")))
			break ;
	}
	ft_memmove(line, current_line, sizeof(t_line));
	clear_unused_lines(hist_lines, current_line->line, line_count);
	exec_key(line, next_key);
	get_next_line(hist_fd, NULL);
}

void
	retreive_hist(t_line *line)
{
	char	*hist_file_path;
	int		fd;

	hist_file_path = ft_getenv(HIST_ENV);
	if (!hist_file_path)
		hist_file_path = DEFAULT_HIST_FILE;
	fd = open(hist_file_path, O_RDONLY);
	loop_hist(line, fd);
	close(fd);
}
