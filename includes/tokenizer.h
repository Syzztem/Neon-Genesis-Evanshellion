/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 16:51:29 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/02 11:46:30 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H
# include "minishell.h"
# define SEPS "|;<>\"\'&()"
# define TOKEN_SPLITTERS "|;<>&() \t\n\v\f\r"

typedef struct	s_token
{
	struct s_token	*next;
	char			*token;
}				t_token;

typedef	size_t	(*t_method)(char *token, char *line);

t_token			*expand_wildcard(char *expr);
char			*parse_variables(char *line);
size_t			add_token(char *token, t_token **list, char *line);
size_t			spaces(char *token, char **line);
size_t			squotes(char *token, char **line);
size_t			dquotes(char *token, char **line);
size_t			seps(char *token, char **line);

#endif
