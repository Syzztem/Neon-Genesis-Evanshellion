/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:48:36 by lothieve          #+#    #+#             */
/*   Updated: 2021/01/19 13:23:02 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMCAPS_H
# define TERMCAPS_H

# define ESC_CHAR '\x1b'
# define BUFF_SIZE 255
# define CURSOR_QUERY "\x1b[6n"
# define CAP_COUNT 2
# define ESC_LEN 3
# include "minishell.h"
# include <curses.h>
# include <term.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <termios.h>


typedef struct	s_point
{
	size_t x;
	size_t y;
}				t_point;

typedef struct	s_line
{
	char	*line;
	size_t	r_cur_pos;
	size_t	len;
	size_t	start_row;
	size_t	max_len;
	t_point cursor_pos;
}				t_line;

typedef struct	termios
				t_term;
typedef void	(*t_cap)(t_line *line);

void			insert_char(t_line *line, char c);
void			delete_char(t_line *line);
void			cap(char *tc);
void			realloc_line(t_line *line);
void			move_left(t_line *line);
void			move_right(t_line *line);
int				ft_putchar(int c);
int				get_term_line(char **buffer);

#endif
