/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 11:22:51 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/16 10:52:47 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"
#define TEMP_HIST_FILE "/tmp/msh_hist_tmp"
#define TRANSFER_BUFF_SIZE 1024

void
	set_line(t_line *line)
{
	go_home(line);
	cap("ce");
	ft_putstr_fd(line->line, 1);
	go_end(line);
}

t_line
	*create_line(t_line *buf, t_line *origin)
{
	buf->r_cur_pos = ft_strlen(buf->line);
	buf->len = buf->r_cur_pos;
	buf->start_row = origin->start_row;
	buf->max_len = buf->len;
	buf->cursor_pos.x = origin->start_row + buf->len;
	buf->cursor_pos.y = origin->cursor_pos.y;
	return (buf);
}

void
	clear_unused_lines(t_line *hist, char *to_keep, size_t size)
{
	while (size-- > 0)
		if (hist[size].line != to_keep)
			free(hist[size].line);
	free(hist);
}

static void
	transfer_file(int fd1, int fd2)
{
	char	buf[TRANSFER_BUFF_SIZE];
	int		ret;

	ret = 1;
	while (ret)
	{
		ret = read(fd2, buf, TRANSFER_BUFF_SIZE);
		write(fd1, buf, ret);
	}
}

void
	add_to_hist(char *cmd)
{
	int		hist_fd;
	int		tmp_fd;
	char	*path;

	if (!*cmd)
		return ;
	path = ft_getenv(HIST_ENV);
	if (!path)
		path = DEFAULT_HIST_FILE;
	hist_fd = open(path, O_CREAT | O_RDWR, 0x1ff);
	tmp_fd = open(TEMP_HIST_FILE, O_RDWR | O_CREAT, 0x1ff);
	ft_putendl_fd(cmd, tmp_fd);
	transfer_file(tmp_fd, hist_fd);
	close(hist_fd);
	close(tmp_fd);
	hist_fd = open(path, O_WRONLY, S_IRUSR | S_IWUSR);
	tmp_fd = open(TEMP_HIST_FILE, O_RDONLY | O_CREAT, S_IRUSR, S_IWUSR);
	transfer_file(hist_fd, tmp_fd);
	close(hist_fd);
	close(tmp_fd);
}
