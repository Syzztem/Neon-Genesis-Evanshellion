/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 16:51:29 by lothieve          #+#    #+#             */
/*   Updated: 2021/01/10 14:41:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H
# include "minishell.h"
# define SEPS "|;<>\"\'"

typedef struct	s_token
{
	struct s_token	*next;
	char			*token;
}				t_token;

typedef	char	*(*t_method)(char **line);

t_token			*expand_wildcard(char *expr);
char			*spaces(char **line);
char			*squotes(char **line);
char			*dquotes(char **line);
char			*seps(char	**line);

#endif
