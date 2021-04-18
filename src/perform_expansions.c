/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_expansions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 11:47:34 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/18 15:46:26 by smaccary         ###   ########.fr       */
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
	while (*ref && !ft_isspace(*ref))
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
	raw_input_len(char *command)
{
	char *ref;

	ref = command;
	while (*ref && !wildcard_len(ref) &&
			(*ref != '$' || (ref != command && *ref == '\\')))
		++ref;
	return (ref - command);
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

char
	*perform_expansions(char *command)
{
	t_token *list;
	char	*ref;
	size_t	len;
	char	*out;

	ref = command;
	list = NULL;
	while (*ref)
	{
		len = wildcard_len(ref);
		if (len)
			ref += add_wildcard(ref, len, &list);
		else if (*ref == '$' && (ref == command || *ref != '\\'))
			ref += add_env(ref, &list);
		else
		{
			len = raw_input_len(ref);
			ft_lstadd_back((t_list **)&list, ft_strndup(ref, len));
			ref += len;
		}
	}
	out = list_to_pure_string(list);
	free_list(list);
	return (out);
}
