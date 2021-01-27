/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 15:08:31 by lothieve          #+#    #+#             */
/*   Updated: 2021/01/27 15:21:27 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <stdio.h>
# include "libft.h"

static const char *g_seps[6] = {">>", "<", ">", "|", ";", NULL};

enum			e_genv
{
	GE_VAL,
	GE_FULL
};

char			**tokenize(char *line);
int				ft_igetenv(char *name);
char			*ft_getenv(char *name);
char			*ft_setenv(char *name, char *value);

#endif
