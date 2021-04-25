/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_term_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:25:51 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/25 10:27:44 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "termcaps.h"
#include <string.h>
#include <errno.h>

void
	move_up(t_line *line)
{
	t_point	relative_cursor;

	get_relative_pos(line->r_cur_pos, &relative_cursor);
	if (relative_cursor.y < 1)
		return ;
	relative_cursor.y--;
	if (relative_cursor.y < 1
	&& line->cursor_pos.x < ft_strlen(PROMPT) % get_term_width())
	{
		go_home(line);
		return ;
	}
	line->cursor_pos.y--;
	line->r_cur_pos = (relative_cursor.y * get_term_width()) 
	- ft_strlen(PROMPT) + line->cursor_pos.x;
	update_cursor(line);
}

void
	move_down(t_line *line)
{
	t_point	relative_cursor;

	get_relative_pos(line->r_cur_pos, &relative_cursor);
	if (relative_cursor.y >= get_line_height(line->len))
		return ;
	if (line->cursor_pos.x > (line->len + ft_strlen(PROMPT)) % get_term_width())
	{
		go_end(line);
		return ;
	}
	line->cursor_pos.y++;
	relative_cursor.y++;
	line->r_cur_pos = (relative_cursor.y * (get_term_width() - 1)) 
	- ft_strlen(PROMPT) + line->cursor_pos.x;
	update_cursor(line);
}


static const t_cap	g_caps[CAP_COUNT] = {
	move_left,
	move_right,
	prev_word,
	next_word,
	move_down,
	move_up,
	go_home,
	go_end,
	retreive_hist
};

/*
** That makes no sense at all but
** #4 is the shift + left key
** %i is the shift + right key
** Now I can die in peace for finding them
** And they both return the same value :)
*/

static const char	*g_capstr[CAP_COUNT] = {
	"kl",
	"kr",
	"#4",
	"%i",
	"#4",
	"#4",
	"kh",
	"@7",
	"ku"
};

int
	get_key(char *key, char do_buf)
{
	int			rd;
	static char	bfrd;

	if (bfrd)
	{
		*key = bfrd;
		bfrd = 0;
		return (0);
	}
	rd = read(0, key, 7);
	if (*key == '\4')
		return (0);
	if (*key == do_buf)
		bfrd = *key;
	key[rd] = '\0';
	return (rd);
}

static t_cap
	exec_cap(char *key)
{
	int 	i;
	char	*tstr;

	i = -1;
	while (++i < CAP_COUNT)
	{
		tstr = tgetstr((char *)g_capstr[i], NULL);
		if (!ft_strncmp(key + 1, tstr + 1, ESC_LEN))
		{
			if (i == 2)
				i += ft_indexof("DCBA", key[5]);
			return (g_caps[i]);
		}
	}
	return (do_nothing);
}

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
	locate_cursor(t_line *line)
{
	int		term_width;
	size_t	prompt_len;

	prompt_len = ft_strlen(PROMPT);
	term_width = get_term_width();
	line->cursor_pos.x = (line->r_cur_pos + prompt_len) % (term_width - 1);
	line->cursor_pos.y += (line->r_cur_pos + prompt_len) / (term_width - 1);
}

void
	wrap_paste(t_line *line)
{
	int	term_width;
	int	term_height;
	int	offset;

	term_width = get_term_width();
	term_height = get_term_height();
	/*if (line->cursor_pos.x == (size_t)term_width)
	{
		line->cursor_pos.x = 0;
		if (line->cursor_pos.y < term_height - 1)
			line->cursor_pos.y++;
	}*/
	offset = 1;
	if (get_last_column(line) > term_height - 1)
	{
		line->start_column--;
		line->cursor_pos.y -= line->len != line->r_cur_pos;
		if (line->r_cur_pos == line->len)
			offset = 0;
	}
	scroll_up_n(term_height - line->cursor_pos.y - offset);
	//else
	//	scroll_up_n(1);
//	locate_cursor(line);
	update_cursor(line);
	//sleep(1);
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

void
	exec_key(t_line *line, char *key)
{
	if (*key == 0x15)
		return (cut_line(line));
	if (*key == 0x19)
		return (paste_line(line));
	if (*key >= 32 && *key < 127)
		return (insert_char(line, *key));
	if (*key == 127)
		return (delete_char(line));
	if (*key == ESC_CHAR)
		return (exec_cap(key)(line));
}

void
	get_cursor(t_point *cursor)
{
	char	cursor_pos[17];
	size_t	i;
	int		rd;


	write(0, CURSOR_QUERY, 4);
	rd = read(1, cursor_pos, 16);
	if (rd < 0)
	{
		perror(strerror(errno));
		exit(errno);
	}
	cursor_pos[rd] = '\0';
	i = 2;
	cursor->y = ft_atoi(cursor_pos + i) - 1;
	while (ft_isdigit(cursor_pos[i]))
		i++;
	cursor->x = ft_atoi(cursor_pos + i + 1) - 1;
}

void
	init_line(t_line *line)
{

	line->line = malloc(BUFF_SIZE);
	ft_bzero(line->line, BUFF_SIZE);
	line->r_cur_pos = 0;
	line->len = 0;
	line->max_len = BUFF_SIZE;
	get_cursor(&(line->cursor_pos));
	line->start_row = line->cursor_pos.x;
	line->start_column = line->cursor_pos.y;
}

int
	get_term_line(char **buffer)
{
	char	key[10];
	t_line	*line;

	line = malloc(sizeof(t_line));
	init_line(line);
	interrupt_singleton(0);
	singleton_line(line, 1);
	while (1)
	{
		if ((get_key(key, 0) == 0 && line->len == 0 && *key == 4))
		{
			free(line->line);
			free(line);
			return (0);
		}
		if (interrupt_singleton(-1))
		{
			interrupt_singleton(0);
			free(line->line);
			init_line(line);
		}
		if (*key == '\n')
		{
			ft_putchar('\n');
			*buffer = line->line;
			add_to_hist(*buffer);
			free(line);
			return (1);
		}
		exec_key(line, key);
	}
	return (1);
}
