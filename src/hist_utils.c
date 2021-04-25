/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 11:22:51 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/25 06:26:27 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"
#define TEMP_HIST_FILE "/tmp/msh_hist_tmp"
#define TRANSFER_BUFF_SIZE 1024

void
	set_line(t_line *line)
{
	write(0, line->line, line->len);
	line->r_cur_pos = line->len;
	//get_cursor(&(line->cursor_pos));
}

t_line
	*create_line(t_line *buf, t_line *origin)
{
	t_point	relative;

	buf->r_cur_pos = ft_strlen(buf->line);
	buf->len = buf->r_cur_pos;
	buf->start_row = origin->start_row;
	buf->max_len = buf->len;
	get_relative_pos(buf->len, &relative);
	buf->cursor_pos.x = relative.x;
	buf->start_column = origin->start_column;
	buf->cursor_pos.y = buf->start_column + relative.y;
	if (buf->cursor_pos.y > get_term_height() - 1)
		buf->start_column -= buf->cursor_pos.y - (get_term_height() - 1);
	buf->cursor_pos.y = buf->start_column + relative.y;
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

	if (!cmd || !*cmd)
		return ;
	path = get_history_path();
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
	free(path);
}
