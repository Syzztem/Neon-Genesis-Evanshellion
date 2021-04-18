/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 16:51:29 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/18 15:35:55 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H
# include "minishell.h"
# define SEPS "|;<>\"\'&()"
# define TOKEN_SPLITTERS "|;<>& \t\n\v\f\r"

typedef t_list t_token;

/* No need to create a new struct for this, t_list can already handle this.
** typedef struct	s_token
** {
** 	struct s_token	*next;
** 	char			*token;
** }				t_token;
*/

typedef	size_t	(*t_method)(char *token, char *line);

t_token			*expand_wildcard(char *expr);
char			*parse_variables(char *line);
void			free_list(t_token *list);
char			*list_to_pure_string(t_token *list);
void			print_list(t_token *list);

#endif
