/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:29:58 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/29 21:55:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

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

	cpy = ft_calloc(line->max_len + BUFF_SIZE, 1);
	if (!cpy)
	{
		free(line);
		exit(1);
	}
	ft_memmove(cpy, line->line, line->max_len);
	free(line->line);
	line->line = cpy;
	line->max_len += BUFF_SIZE;
}

int		key_is(char *key, char *cap)
{
	if (ft_strncmp(key, tgetstr(cap, NULL), ESC_LEN))
		return (0);
	return (1);
}
