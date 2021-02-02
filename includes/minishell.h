/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 15:08:31 by lothieve          #+#    #+#             */
/*   Updated: 2021/02/01 17:07:21 by lothieve         ###   ########.fr       */
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

static const char *g_seps[6] = {">>", "<", ">", "|", ";", NULL};

typedef void	(*t_builtin)(char **av, char **envp);
typedef struct termios	t_term;

int				get_term_line(char **buffer);
char			**tokenize(char *line);

int				ft_igetenv(char *name);
char			*ft_getenv(char *name);
char			*ft_lgetenv(char *line);
void			ft_unsetenv(char *name);
char			*ft_setenv(char *name, char *value);

void			builtin_cd(char **av, char **envp);
void			builtin_env(char **av, char **envp);
void			builtin_pwd(char **av, char **envp);
void			builtin_echo(char **av, char **envp);
void			builtin_exit(char **av, char **envp);
void			builtin_unset(char **av, char **envp);
void			builtin_export(char **av, char **envp);

void			cap(char *tc);
#endif
