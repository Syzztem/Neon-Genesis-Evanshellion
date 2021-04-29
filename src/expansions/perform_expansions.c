/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_expansions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 11:47:34 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/29 21:37:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static size_t
	wildcard_len(char *command)
{
	int		is;
	char	*ref;

	ref = command;
	is = 0;
	while (*ref && *ref != SPACE)
	{
		if (*ref == '*' && (ref == command || *(ref - 1) != '\\'))
			is = 1;
		++ref;
	}
	if (is)
		return (ref - command);
	return (0);
}

static size_t
	add_env(char *command, t_token **list)
{
	char *env;
	char *ref;

	ref = command;
	env = ft_lgetenv(++ref);
	if (env)
		ft_lstadd_back((t_list **)list, ft_strdup(env));
	else if (*ref == '?')
	{
		ft_lstadd_back((t_list **)list, ft_itoa(g_exit_status));
		return (2);
	}
	while (ft_isalnum(*ref) || *ref == '_')
		++ref;
	return (ref - command);
}

static size_t
	add_wildcard(char *command, size_t len, t_token **list)
{
	ft_lstmerge((t_list **)list, (t_list *)
			expand_wildcard(ft_strndup(command, len)));
	return (len);
}

void
	do_expansions(char **quote, char **ref, char *command, t_token **alst)
{
	size_t	len;

	if (!*(*quote) && (ft_strchr("\"'", *(*ref))
	&& (*ref) != command && (*ref)[-1] != '\\'))
		(*quote) = (*ref);
	else if (*(*quote) == *(*ref))
		(*quote) = "\0";
	len = wildcard_len((*ref));
	if (len && *(*quote) != '\'')
		(*ref) += add_wildcard((*ref), len, alst);
	else if (*(*quote) != '\'' && *(*ref) == '$'
	&& ((*ref) == command || (*ref)[-1] != '\\'))
		(*ref) += add_env((*ref), alst);
	else
		ft_lstadd_back((t_list **)alst, ft_strndup((*ref)++, 1));
}

char
	*perform_expansions(char *command)
{
	t_token *list;
	char	*ref;
	char	*out;
	char	*quote;

	if (!command)
		return (NULL);
	ref = command;
	list = NULL;
	quote = "\0";
	while (*ref)
		do_expansions(&quote, &ref, command, &list);
	out = list_to_pure_string(list);
	free_list(list);
	return (out);
}

/*
** char
** 	*perform_expansions(char *command)
** {
** 	t_token *list;
** 	char	*ref;
** 	size_t	len;
** 	char	*out;
** 	char	*quote;
**
** 	if (!command)
** 		return (NULL);
** 	ref = command;
** 	list = NULL;
** 	quote = "\0";
** 	while (*ref)
** 	{
** 		if (!*quote && (ft_strchr("\"'", *ref)
** 		&& ref != command && ref[-1] != '\\'))
** 			quote = ref;
** 		else if (*quote == *ref)
** 			quote = "\0";
** 		len = wildcard_len(ref);
** 		if (len && *quote != '\'')
** 			ref += add_wildcard(ref, len, &list);
** 		else if (*quote != '\'' && *ref == '$'
** 		&& (ref == command || ref[-1] != '\\'))
** 			ref += add_env(ref, &list);
** 		else
** 			ft_lstadd_back((t_list **)&list, ft_strndup(ref++, 1));
** 	}
** 	out = list_to_pure_string(list);
** 	free_list(list);
** 	return (out);
** }
*/
