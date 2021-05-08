/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 15:08:31 by lothieve          #+#    #+#             */
/*   Updated: 2021/05/09 00:18:11 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <stdio.h>
# include <curses.h>
# include <term.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <termios.h>
# include <signal.h>
# include "termcaps.h"
# include "libft.h"
# define PROMPT "EVA-04$ "
# define ML_PROMPT "> "

# define SPACE ' '

extern int	g_exit_status;

typedef int	(*t_builtin)(char **av, char **envp);
typedef struct termios	t_term;

void            print_file_error(char *filename);
size_t			argv_len(char **argv);
int				minishell(void);
int				minishell_non_interactive(void);
void			init_signals(void);
char			*strjoin_newline_free(char *s1, char *s2);
char			*strjoin_newline(char *s1, char *s2);
void			free_env(void);
int				verify_line(char *line);
char			*prompt(void);
char			*set_prompt(char *prompt);
sig_t			blank_fork(int sig);
sig_t			interrupt_blank(int a);
int				interrupt_singleton(int value);
int				get_term_line(char **buffer);
char			**tokenize(char *line, char *end);
char			*remove_quotes_and_do_escape(char *line, char **end);
char			**split_line(char *line);
char			*remove_quotes(char *line);
char			*perform_expansions(char *command);
int				complete_line(char **line, int ret);

char			**token_separators(void);
int				ft_igetenv(char *name);
char			*ft_getenv(char *name);
char			*ft_lgetenv(char *line);
void			ft_unsetenv(char *name);
char			*ft_setenv(char *name, char *value);
void			copy_env(void);

void			multi_free(void **arr, size_t nb);

int				is_builtin(char *command);
int				exec_builtin(char **av, char **envp);

void			free_tab(char **table);
size_t			tab_size(char **table);
char			**dup_tab(char **table);

int				builtin_cd(char **av, char **envp);
int				builtin_env(char **av, char **envp);
int				builtin_pwd(char **av, char **envp);
int				builtin_echo(char **av, char **envp);
int				builtin_exit(char **av, char **envp);
int				builtin_unset(char **av, char **envp);
int				builtin_export(char **av, char **envp);
int				builtin_parenthesis(char **av, char **envp);
int				print_exit(void);
void			p_builtin_error(char *name, char *arg, char *error_msg);

char			*find_exec(char *path_buf, char *name);
int				handle_error(char *command, char *arg, char *errmsg);

void			cap(char *tc);
int				ft_isatty(int fd);
int				is_shell_interactive(void);
int				exec_line(char *line);
void			ft_append_env(char *name, char *value);
#endif
