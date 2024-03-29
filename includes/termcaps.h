/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:48:36 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/30 20:29:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMCAPS_H
# define TERMCAPS_H

# define ESC_CHAR '\x1b'
# define BUFF_SIZE 255
# define CURSOR_QUERY "\x1b[6n"
# define CAP_COUNT 9
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
# include <sys/ioctl.h>

typedef struct	s_point
{
	size_t		x;
	ssize_t		y;
}				t_point;

typedef struct	s_line
{
	char	*line;
	size_t	r_cur_pos;
	size_t	len;
	size_t	start_row;
	size_t	start_column;
	size_t	max_len;
	t_point	cursor_pos;
}				t_line;

typedef void	(*t_cap)(t_line *line);

t_cap			*g_caps(void);
char			**g_capstr(void);
t_cap			exec_cap(char *key);
void			interrupt_line(t_line *line);
t_line			*realloc_lines(t_line *h, size_t *size, t_line **current_line);
t_line			*change_line(t_line *new, size_t current_column);
t_line			*next_line(t_line *o, t_line *h, size_t *linec, int hist_fd);
t_line			*prev_line(t_line *hist_lines, t_line *current);
void			move_up(t_line *line);
void			move_down(t_line *line);
void			locate_cursor(t_line *line);
char			*pastebin_manager(char *input, int mode);
void			cut_line(t_line *line);
void			wrap_paste(t_line *line);
char			*join_paste(t_line *l, char *p, size_t len, size_t new_len);
void			paste_line(t_line *line);
void			scroll_up_n(int n);
void			wrap_line(t_line *line);
t_line			*singleton_line(t_line *line, int mode);
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
void			print_line(t_line *line);
void			get_cursor(t_point *cursor);
void			clear_line(t_line *line);
void			get_term_size(int *width_ptr, int *height_ptr);
int				get_term_width(void);
int				get_term_height(void);
int				get_start_column(t_line *line);
void			update_cursor(t_line *line);
void			get_relative_pos(size_t r_pos, t_point *cursor);
int				get_line_height(size_t len);
int				get_last_column(t_line *line);
#endif
