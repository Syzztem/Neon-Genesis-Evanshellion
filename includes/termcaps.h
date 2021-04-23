/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:48:36 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/23 16:24:04 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMCAPS_H
# define TERMCAPS_H

# define ESC_CHAR '\x1b'
# define BUFF_SIZE 255
# define CURSOR_QUERY "\x1b[6n"
# define CAP_COUNT 7
# define ESC_LEN 3
# define DEFAULT_HIST_FILE ".minishell_history"
# define HIST_ENV "HOME"
# define LINE_ALLOC_SIZE 5
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

typedef void	(*t_cap)(t_line *line);


void			init_line(t_line *line);
void			insert_char(t_line *line, char c);
void			delete_char(t_line *line);
void			go_home(t_line *line);
void			go_end(t_line *line);
void			prev_word(t_line *line);
void			next_word(t_line *line);
void			cap(char *tc);
void			realloc_line(t_line *line);
void			move_left(t_line *line);
void			move_right(t_line *line);
void			retreive_hist(t_line *line);
void			do_nothing(t_line *line);
void			add_to_hist(char *cmd);
int				get_key(char *key, char do_buf);
void			exec_key(t_line *line, char *key);
void			clear_unused_lines(t_line *hist, char *to_keep, size_t size);
t_line			*create_line(t_line *buf, t_line *origin);
void			set_line(t_line	*line);
int				key_is(char *key, char *cap);
int				ft_putchar(int c);
int				get_term_line(char **buffer);
void			move_cursor(int x, int y);
char			*get_history_path(void);

#endif
