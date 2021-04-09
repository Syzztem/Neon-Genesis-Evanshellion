/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 15:08:31 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/09 11:35:29 by lothieve         ###   ########.fr       */
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
# include "libft.h"
# include "global.h"
# define PROMPT "EVA-04$ "

static const char	*g_seps[] = {"<<", ">>","<", ">", "|", ";",
	"&&", "&", "||", "(", ")", NULL};

typedef int	(*t_builtin)(char **av, char **envp);
typedef struct termios	t_term;

int				get_term_line(char **buffer);
char			**tokenize(char *line);
char			**split_line(char *line);
char			*remove_quotes(char *line);
int				complete_line(char **line);

int				ft_igetenv(char *name);
char			*ft_getenv(char *name);
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
