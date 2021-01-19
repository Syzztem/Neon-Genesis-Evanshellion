/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_term_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:25:51 by lothieve          #+#    #+#             */
/*   Updated: 2021/01/19 13:17:57 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

static const t_cap
	g_caps[CAP_COUNT] = {move_left, move_right};

static const char
	*g_capstr[CAP_COUNT] = {"kl", "kr"};

static void
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
		if (!ft_strncmp(key + 1, tgetstr((char *)g_capstr[i], NULL) + 1, ESC_LEN))
			return (g_caps[i]);
	return (NULL);
}

static void
	exec_key(t_line *line, char *key)
{
	if (*key >= 32 && *key < 127)
		return (insert_char(line, *key));
	if (*key == 127)
		return (delete_char(line));
	if (*key == ESC_CHAR)
		return (exec_cap(key)(line));
}

void
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
	while (ft_isdigit(cursor_pos[i]))
		i++;
	line->cursor_pos.x = ft_atoi(cursor_pos + i + 1);
	line->start_row = line->cursor_pos.x;
}

int
	get_term_line(char **buffer)
{
	char	key[5];
	t_line	line;
	
	init_line(&line);
//	printf("line struct:\n\t.line = %p\n\t.r_cur_pos = %zu\n\t.len = %zu\n\t.start_row = %zu\n\t.max_len = %zu\n\t.cursor_pos = %zu, %zu\n",
//			line.line, line.r_cur_pos, line.len, line.start_row, line.max_len, line.cursor_pos.x, line.cursor_pos.y);
	while (1)
	{
		get_key(key);
		if (*key == '\n' && line.r_cur_pos == line.len)
		{
			ft_putchar('\n');
			*buffer = line.line;
			return (1);
		}
		exec_key(&line, key);
	}
	return (0);
}
