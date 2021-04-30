/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 15:08:31 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/30 14:36:08 by smaccary         ###   ########.fr       */
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

#define PARGV(argv) if (DEBUG) {printf("%s:%d:[%s]: ", __FILE__, __LINE__, #argv) ; print_argv(argv);}

extern int	g_exit_status;

static const char	*g_seps[] = {"<<", ">>","<", ">", "||", "|", ";",
	"&&", "&", "(", ")", NULL};

typedef int	(*t_builtin)(char **av, char **envp);
typedef struct termios	t_term;


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
char			**tokenize(char *line);
char			**split_line(char *line);
char			*remove_quotes(char *line);
char			*perform_expansions(char *command);
int				complete_line(char **line, int ret);


int				ft_igetenv(char *name);
char			*ft_getenv(char *name) ;
char			*ft_lgetenv(char *line);
void			ft_unsetenv(char *name);
char			*ft_setenv(char *name, char *value);
void			copy_env(void);

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
int             builtin_parenthesis(char **av, char **envp);
int				print_exit(void);
void			p_builtin_error(char *name, char *arg, char *error_msg);

char			*find_exec(char *path_buf, char *name);
int				handle_error(char *command, char *arg, char *errmsg);

void			cap(char *tc);
int				ft_isatty(int fd);
int				is_shell_interactive(void);
int				exec_line(char **commands);
#endif
