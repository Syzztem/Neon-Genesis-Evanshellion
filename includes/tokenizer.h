/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 16:51:29 by lothieve          #+#    #+#             */
/*   Updated: 2021/05/02 20:14:36 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H
# include "minishell.h"
# define SEPS "|;<>\"\'&()"
# define TOKEN_SPLITTERS "|;<>& \t\n\v\f\r"
# define TO_ESCAPE "|;&<>$"

# define SQ_ESCAPES " \t\n\v\f\r;&|\"*<>()\\$"
# define DQ_ESCAPES " \t\n\v\f\r;&|\'*<>()"
# define DQ_ESCAPES_2 " \t\n\v\f\r;&|*<>()"
# define TO_ESC_NO_QUOTE  "$\\\"'"
# define TO_ESC_DB_QUOTE  "$\\\""

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
int				check_escape(char *current, char *quote);
size_t			wildcard_len(char *command);
size_t			add_wildcard(char *command, size_t len, t_token **list);
#endif
