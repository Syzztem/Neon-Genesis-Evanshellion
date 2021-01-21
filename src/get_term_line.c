/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_term_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:25:51 by lothieve          #+#    #+#             */
/*   Updated: 2021/01/21 14:44:05 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

static const t_cap	g_caps[CAP_COUNT] = {move_left,
	move_right, go_home, go_end, retreive_hist};

static const char	*g_capstr[CAP_COUNT] = {"kl", "kr", "kN", "kP", "ku"};

void
	get_key(char *key)
{
	int	rd;

	rd = read(0, key, 1);
	if (*key == ESC_CHAR)
		rd += read(0, key + 1, 3);
	key[rd] = '\0';
}

static t_cap
	exec_cap(char *key)
{
	int i;

	i = -1;
	while (++i < CAP_COUNT)
		if (!ft_strncmp(key + 1, tgetstr((char *)g_capstr[i], NULL) + 1,
			ESC_LEN))
			return (g_caps[i]);
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
	char	cursor_pos[16];
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
	if (line->cursor_pos.y != tgetnum("li"))
		line->cursor_pos.y--;
	while (ft_isdigit(cursor_pos[i]))
		i++;
	line->cursor_pos.x = ft_atoi(cursor_pos + i + 1);
	line->start_row = line->cursor_pos.x - 1;
}

int
	get_term_line(char **buffer)
{
	char	key[5];
	t_line	*line;

	line = malloc(sizeof(t_line));
	init_line(line);
	while (1)
	{
		get_key(key);
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
	return (0);
}
