/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 16:51:29 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/29 21:14:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H
# include "minishell.h"
# define SEPS "|;<>\"\'&()"
# define TOKEN_SPLITTERS "|;<>& \t\n\v\f\r"
# define TO_ESCAPE "|;&<>$"


typedef struct	s_token
{
	struct s_token	*next;
	char			*token;
}				t_token;

typedef	size_t	(*t_method)(char *token, char *line);

t_token			*expand_wildcard(char *expr);
char			*parse_variables(char *line);
void			free_list(t_token *list);
char			*list_to_pure_string(t_token *list);
void			print_list(t_token *list);
void			clean_backslashes(char **tokens);
void			clear_escaped_quotes(char *command);
#endif
