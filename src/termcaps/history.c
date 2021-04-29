/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 13:22:07 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/29 22:59:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static void
	end_hist(t_line *line, t_line *current_line,
				int hist_fd)
{
	ft_memmove(line, current_line, sizeof(t_line));
	singleton_line(line, 1);
	interrupt_line(line);
	get_next_line(hist_fd, NULL);
	close(hist_fd);
}

static void
	check_lines(t_line **hist_lines, t_line **current_line, size_t *hist_size,
	size_t line_count)
{
	if (line_count == *hist_size)
		*hist_lines = realloc_lines(*hist_lines, hist_size, current_line);
}

static void
	loop_hist(t_line *line, int hist_fd, t_line *hist_lines, size_t line_count)
{
	size_t	hist_size;
	char	next_key[50];
	t_line	*current_line;

	hist_size = LINE_ALLOC_SIZE;
	current_line = hist_lines;
	while (!interrupt_singleton(-1))
	{
		check_lines(&hist_lines, &current_line, &hist_size, line_count);
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
	}
	end_hist(line, current_line, hist_fd);
	clear_unused_lines(hist_lines, current_line->line, line_count);
	exec_key(line, next_key);
}

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
		clear_line(line);
		loop_hist(line, fd, hist_lines, line_count);
	}
	free(hist_file_path);
}
