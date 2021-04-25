/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 13:22:07 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/25 07:10:34 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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
	return (create_line(current - 1, current));
}

static void
	loop_hist(t_line *line, int hist_fd, t_line *hist_lines, size_t line_count)
{
	size_t	hist_size;
	char	next_key[50];
	t_line	*current_line;
	t_line	tmp;

	clear_line(line);
	hist_size = LINE_ALLOC_SIZE;
	current_line = hist_lines;
	while (!interrupt_singleton(-1))
	{		
		if (line_count == hist_size)
			hist_lines = realloc_lines(hist_lines, &hist_size, &current_line);
		if (key_is(next_key, "kd"))
			current_line = prev_line(hist_lines, current_line);
		else
			current_line = next_line(current_line, hist_lines, &line_count,
				hist_fd);
		set_line(current_line);
		singleton_line(current_line, 1);
		get_key(next_key, '\n');
		if (!(key_is(next_key, "ku") || key_is(next_key, "kd"))
		|| interrupt_singleton(-1))
			break ;
		clear_line(current_line);
		//sleep(2);
	}
	ft_memmove(line, current_line, sizeof(t_line));
	clear_unused_lines(hist_lines, current_line->line, line_count);
	if (interrupt_singleton(-1))
	{
		interrupt_singleton(0);
		free(line->line);
		init_line(line);
	}
	exec_key(line, next_key);
	get_next_line(hist_fd, NULL);
}

/*
** void
** 	retreive_hist(t_line *line)
** {
** 	char	*hist_file_path;
** 	int		fd;
** 	t_line	*hist_lines;
** 	size_t	line_count;
** 
** 	hist_lines = ft_calloc(sizeof(t_line), LINE_ALLOC_SIZE);
** 	line_count = 1;
** 	*hist_lines = *line;
** 	hist_file_path = ft_getenv(HIST_ENV);
** 	if (!hist_file_path)
** 		hist_file_path = DEFAULT_HIST_FILE;
** 	fd = open(hist_file_path, O_RDONLY);
** 	if (fd == -1)
** 		return ;
** 	loop_hist(line, fd, hist_lines, line_count);
** 	close(fd);
** }
** 
*/

/*
** returns malloced history path string. 
*/
char
	*get_history_path(void)
{
	char	*hist_file_path;

	hist_file_path = ft_getenv(HIST_ENV);
	if (!hist_file_path)
		hist_file_path = ft_strdup(DEFAULT_HIST_FILE);
	else
		hist_file_path = ft_strjoin(hist_file_path, "/" DEFAULT_HIST_FILE);
	return (hist_file_path);
}

t_line
	*singleton_line(t_line *line, int mode)
{
	static t_line	*stored = NULL;

	if (mode)
		stored = line;
	return (stored);
}

void
	retreive_hist(t_line *line)
{
	char	*hist_file_path;
	int		fd;
	t_line	*hist_lines;
	size_t	line_count;

	hist_lines = ft_calloc(sizeof(t_line), LINE_ALLOC_SIZE);
	line_count = 1;
	*hist_lines = *line;
	hist_file_path = get_history_path();
	if (!hist_file_path)
		return ;
	fd = open(hist_file_path, O_RDONLY);
	if (fd != -1)
	{
		loop_hist(line, fd, hist_lines, line_count);
		close(fd);
	}
	free(hist_file_path);
}

