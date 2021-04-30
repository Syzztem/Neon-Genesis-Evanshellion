/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 21:08:43 by user42            #+#    #+#             */
/*   Updated: 2021/04/30 16:45:25 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "tokenizer.h"
#include "vector.h"

void
	expand_argv(char *argv, t_vector *new)
{
	char	**current;
	char	*expanded;
	char	*dequoted;
	char	**splitted;

	expanded = perform_expansions(argv);
	splitted = split_quotes(expanded);
	free(expanded);
	if (!splitted)
		return ;
	current = splitted;
	while (*current)
	{
		dequoted = remove_quotes(*current);
		vector_append(new, &dequoted, 1);
		free(*current);
		current++;
	}
	free(splitted);
}

void
	extract_redir_tokens(char **tokens, t_vector *argv_vect)
{
	char **current;

	current = tokens;
	while (*current)
	{
		expand_argv(*current, argv_vect);
		current++;
	}
}

static int
	parse_redirect(char **current, t_vector *argv_vect, t_vector *redir_vector)
{
	char		**tokenized;
	char		*expanded;
	char		*dequoted;
	char		*copy;

	tokenized = split_quotes(current[1]);
	extract_redir_tokens(tokenized + 1, argv_vect);
	if (!tokenized[0])
		return (0);
	expanded = perform_expansions(tokenized[0]);
	free_tokens(tokenized);
	dequoted = remove_quotes(expanded);
	free(expanded);
	copy = ft_strdup(*current);
	vector_append(redir_vector, &copy, 1);
	vector_append(redir_vector, &dequoted, 1);
	return (1);
}

void
	expand_redir(char ***redir_ptr, t_vector *argv_vect)
{
	char		**current;
	t_vector	*redir_vector;

	current = *redir_ptr;
	redir_vector = new_vector(4, sizeof(char **));
	while (*current)
	{
		if (is_redirect(*current))
		{
			if (!parse_redirect(current, argv_vect, redir_vector))
				break ;
			current++;
		}
		else
			expand_argv(*current, argv_vect);
		current++;
	}
	vector_append(redir_vector, current, 1);
	free_tokens(*redir_ptr);
	*redir_ptr = redir_vector->bytes;
	free(redir_vector);
}

void
	expand_command(t_command *command)
{
	t_vector	*v;

	if (command->expanded)
		return ;
	command->expanded = 1;
	v = new_vector(20, sizeof(char **));
	expand_argv(command->cmd, v);
	expand_redir(&(command->redirections), v);
	free_tokens(command->argv);
	command->argv = v->bytes;
	command->cmd = get_command_path(command->argv[0]);
	free(v);
	return ;
}
