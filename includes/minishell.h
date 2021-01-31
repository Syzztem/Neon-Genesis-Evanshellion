/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 15:08:31 by lothieve          #+#    #+#             */
/*   Updated: 2021/01/28 15:43:40 by lothieve         ###   ########.fr       */
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

#endif
