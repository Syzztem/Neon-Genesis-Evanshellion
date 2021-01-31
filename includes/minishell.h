/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 15:08:31 by lothieve          #+#    #+#             */
/*   Updated: 2021/01/31 14:04:29 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <stdio.h>
# include "libft.h"

static const char *g_seps[6] = {">>", "<", ">", "|", ";", NULL};

char			**tokenize(char *line);
int				ft_igetenv(char *name);
char			*ft_lgetenv(char *line);
char 			*ft_getenv(char *name);
char			*ft_setenv(char *name, char *value);
int				get_term_line(char **buffer);

#endif
