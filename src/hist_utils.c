/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 11:22:51 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/02 15:49:16 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"
#define TEMP_HIST_FILE "/tmp/msh_hist_tmp"

void	set_line(t_line *line)
{
	go_home(line);
	cap("ce");
	ft_putstr_fd(line->line, 1);
	go_end(line);
}

t_line	*create_line(t_line *buf, t_line *origin)
{
	buf->r_cur_pos = ft_strlen(buf->line);
	buf->len = buf->r_cur_pos;
	buf->start_row = origin->start_row;
	buf->max_len = buf->len;
	buf->cursor_pos.x = origin->start_row + buf->len;
	buf->cursor_pos.y = origin->cursor_pos.y;
	return (buf);
}

void	clear_unused_lines(t_line *hist, char *to_keep, size_t size)
{
	while (size-- > 0)
		if (hist[size].line != to_keep)
			free(hist[size].line);
	free(hist);
}

void	add_to_hist(char *cmd)
{
	int		fd;
	char	*path;

	path = ft_getenv(HIST_ENV);
	if (!path)
		path = DEFAULT_HIST_FILE;
	fd = open(path, O_CREAT | O_RDONLY, S_IRUSR | S_IWUSR);
	ft_putendl_fd(cmd, fd);
	close(fd);
}
