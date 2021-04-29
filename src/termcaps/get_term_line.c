/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_term_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:25:51 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/29 23:09:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "termcaps.h"
#include <string.h>
#include <errno.h>
#include "garbage_collector.h"

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

t_cap
	exec_cap(char *key)
{
	int		i;
	char	*tstr;

	i = -1;
	while (++i < CAP_COUNT)
	{
		tstr = tgetstr((char *)g_capstr[i], NULL);
		if (!ft_strncmp(key + 1, tstr + 1, ESC_LEN))
		{
			if (i == 2)
			{
				i += ft_indexof("DCBA", key[5]);
			}
			return (g_caps[i]);
		}
	}
	return (do_nothing);
}

void
	init_line(t_line *line)
{
	line->line = ft_calloc(BUFF_SIZE, 1);
	line->r_cur_pos = 0;
	line->len = 0;
	line->max_len = BUFF_SIZE;
	get_cursor(&(line->cursor_pos));
	line->start_row = line->cursor_pos.x;
	line->start_column = line->cursor_pos.y;
}

int
	end_input(t_line *line, char **buffer)
{
	ft_putchar('\n');
	*buffer = line->line;
	add_to_hist(*buffer);
	free(line);
	return (1);
}

int
	get_term_line(char **buffer)
{
	char	key[12];
	t_line	*line;

	line = malloc(sizeof(t_line));
	init_line(line);
	interrupt_singleton(0);
	singleton_line(line, 1);
	while (1)
	{
		if ((get_key(key, 0) == 0 && line->len == 0 && *key == 4))
		{
			free_line(line);
			return (0);
		}
		if (interrupt_singleton(-1) && set_prompt(PROMPT))
		{
			interrupt_singleton(0);
			free(line->line);
			init_line(line);
		}
		if (*key == '\n')
			return (end_input(line, buffer));
		exec_key(line, key);
	}
	return (1);
}
