/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:29:58 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/24 23:18:41 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

void
	get_term_size(int *width_ptr, int *height_ptr)
{
    struct winsize	ws;
	int				width;
	int				height;

    if (ioctl(0, TIOCGWINSZ, &ws) == 0)
	{
        width = ws.ws_col;
        height = ws.ws_row;
    }
	else
	{
        width = -1;
		height = -1;
	}
	if (width_ptr)
		*width_ptr = width;
	if (height_ptr)
		*height_ptr = height;
}

int
	get_term_width(void)
{
	int	width;
	
	get_term_size(&width, NULL);
	return (width);
}

int
	get_term_height(void)
{
	int	height;
	
	get_term_size(NULL, &height);
	return (height);
}

int		ft_putchar(int c)
{
	return (write(1, &c, 1));
}

void	cap(char *tc)
{
	char *tstr;

	tstr = tgetstr(tc, NULL);
	tputs(tstr, 1, ft_putchar);
}

void	realloc_line(t_line *line)
{
	char *cpy;

	cpy = malloc(line->max_len + BUFF_SIZE);
	ft_memmove(cpy, line->line, line->max_len + 1);
	free(line->line);
	line->line = cpy;
	line->max_len += BUFF_SIZE;
}

void	move_cursor(int x, int y)
{
	tputs(tgoto(tgetstr("cm", NULL), x, y), 1, ft_putchar);
}

int		key_is(char *key, char *cap)
{
	if (ft_strncmp(key, tgetstr(cap, NULL), ESC_LEN))
		return (0);
	return (1);
}
