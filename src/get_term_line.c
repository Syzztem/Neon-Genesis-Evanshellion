/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_term_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:25:51 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/03 16:02:38 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

static const t_cap	g_caps[CAP_COUNT] = {
	move_left,
	move_right,
	prev_word,
	next_word,
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
	rd = read(0, key, 1);
	if (*key == '\4')
		return (0);
	if (*key == do_buf)
		bfrd = *key;
	if (*key == ESC_CHAR)
		rd += read(0, key + 1, 6);
	key[rd] = '\0';
	return (rd);
}

static t_cap
	exec_cap(char *key)
{
	int i;

	i = -1;
	while (++i < CAP_COUNT)
	{
		if (!ft_strncmp(key + 1, tgetstr((char *)g_capstr[i], NULL) + 1,
			ESC_LEN))
		{
			return (g_caps[i]);
		}
	}
	return (do_nothing);
}

void
	exec_key(t_line *line, char *key)
{
	if (*key >= 32 && *key < 127)
		return (insert_char(line, *key));
	if (*key == 127)
		return (delete_char(line));
	if (*key == ESC_CHAR)
		return (exec_cap(key)(line));
}

static void
	init_line(t_line *line)
{
	char	cursor_pos[17];
	int		rd;
	size_t	i;

	line->line = malloc(BUFF_SIZE);
	ft_bzero(line->line, BUFF_SIZE);
	line->r_cur_pos = 0;
	line->len = 0;
	line->max_len = BUFF_SIZE;
	write(0, CURSOR_QUERY, 4);
	rd = read(1, cursor_pos, 16);
	cursor_pos[rd] = '\0';
	i = 2;
	line->cursor_pos.y = ft_atoi(cursor_pos + i);
	if (line->cursor_pos.y != (size_t)tgetnum("li"))
		line->cursor_pos.y--;
	while (ft_isdigit(cursor_pos[i]))
		i++;
	line->cursor_pos.x = ft_atoi(cursor_pos + i + 1);
	line->start_row = line->cursor_pos.x - 1;
}

int
	get_term_line(char **buffer)
{
	char	key[10];
	t_line	*line;

	line = malloc(sizeof(t_line));
	init_line(line);
	while (1)
	{
		if (get_key(key, 0) == 0 && line->len == 0)
		{
			free(line->line);
			free(line);
			return (0);
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
