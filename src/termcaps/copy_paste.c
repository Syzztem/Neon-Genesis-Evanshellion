/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_paste.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 19:28:09 by user42            #+#    #+#             */
/*   Updated: 2021/04/29 21:50:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char
	*pastebin_manager(char *input, int mode)
{
	static char	*pastebin = NULL;

	if (mode)
	{
		free(pastebin);
		pastebin = input;
	}
	return (pastebin);
}

void
	cut_line(t_line *line)
{
	if (!line->len)
		return ;
	pastebin_manager(ft_strndup(line->line, line->r_cur_pos), 1);
	line->len -= line->r_cur_pos;
	ft_memmove(line->line, line->line + line->r_cur_pos, line->len);
	line->line[line->len] = 0;
	clear_line(line);
	write(0, line->line, line->len);
	line->r_cur_pos = 0;
	update_cursor(line);
}

void
	wrap_paste(t_line *line)
{
	int	term_width;
	int	term_height;
	int	offset;

	term_width = get_term_width();
	term_height = get_term_height();
	offset = 1;
	if (get_last_column(line) > term_height - 1)
	{
		line->start_column--;
		line->cursor_pos.y -= line->len != line->r_cur_pos;
		if (line->r_cur_pos == line->len)
			offset = 0;
	}
	scroll_up_n(term_height - line->cursor_pos.y - offset);
	update_cursor(line);
}

char
	*join_paste(t_line *line, char *paste, size_t paste_len, size_t new_len)
{
	char		*new;
	char		*head;

	new = ft_calloc(new_len + 1, 1);
	head = ft_memmove(new, line->line, line->r_cur_pos);
	head += line->r_cur_pos;
	ft_memmove(head, paste, paste_len);
	head += paste_len;
	ft_memmove(head, line->line + line->r_cur_pos,
					line->len - line->r_cur_pos);
	return (new);
}

void
	paste_line(t_line *line)
{
	char		*paste;
	char		*new;
	size_t		paste_len;
	size_t		new_len;

	paste = pastebin_manager(NULL, 0);
	if (!paste)
		return ;
	paste_len = ft_strlen(paste);
	new_len = line->len + paste_len;
	new = join_paste(line, paste, paste_len, new_len);
	line->len = new_len;
	line->max_len = new_len;
	line->r_cur_pos += paste_len;
	free(line->line);
	line->line = new;
	wrap_paste(line);
	clear_line(line);
	write(0, line->line, line->len);
	locate_cursor(line);
	if (line->r_cur_pos == line->len)
		go_end(line);
	else
		update_cursor(line);
}
