/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 16:51:29 by lothieve          #+#    #+#             */
/*   Updated: 2021/01/12 11:23:08 by lothieve         ###   ########.fr       */
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

typedef	void	(*t_method)(char **line, t_token **list);

t_token			*expand_wildcard(char *expr);
void			spaces(char **line, t_token **list);
void			squotes(char **line, t_token **list);
void			dquotes(char **line, t_token **list);
void			seps(char **line, t_token **list);

#endif
