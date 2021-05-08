/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 21:08:43 by user42            #+#    #+#             */
/*   Updated: 2021/05/09 00:31:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "tokenizer.h"
#include "vector.h"
#include "minishell.h"
#include "parser.h"

char
	**dequote_tokens(char **tokens)
{
	char	*dequoted;
	char	**new;
	size_t	i;

	new = ft_calloc(argv_len(tokens) + 1, sizeof(char **));
	i = 0;
	while (tokens[i])
	{
		dequoted = remove_quotes(tokens[i]);
		new[i] = dequoted;
		i++;
	}
	return (new);
}

char
	**expand_and_dequote_tokens(char **tokens)
{
	char	*expanded;
	char	*dequoted;
	char	**new;
	size_t	i;

	new = ft_calloc(argv_len(tokens) + 1, sizeof(char **));
	i = 0;
	while (tokens[i])
	{
		if (!(expanded = perform_expansions(tokens[i])))
		{
			free(new);
			return (NULL);
		}
		dequoted = remove_quotes(expanded);
		free(expanded);
		if (!dequoted)
		{
			free(new);
			return (NULL);
		}
		new[i] = dequoted;
		i++;
	}
	return (new);
}

void
	expand_argv(char **argv, t_vector *new)
{
	char	**current;
	char	*expanded;
	char	*dequoted;
	char	**splitted;
	char	*end;

	current = argv;
	while (*current)
	{
		if (!(expanded = perform_expansions(*current)))
			return ;
		if (!(dequoted = remove_quotes_and_do_escape(expanded, &end)))
		{
			free(expanded);
			return ;
		}
		if (!(splitted = tokenize(dequoted, end)))
		{
			multi_free((void *[3]){dequoted, expanded}, 2);
			return ;
		}
		vector_append(new, splitted, argv_len(splitted));
		multi_free((void *[3]){dequoted, splitted, expanded}, 3);
		current++;
	}
}

void
	expand_redir(char ***redir_ptr)
{
	char	**new;

	new = expand_and_dequote_tokens(*redir_ptr);
	free_tokens(*redir_ptr);
	*redir_ptr = new;
}

void
	expand_command(t_command *command)
{
	t_vector	*argv_vector;
	char		**splitted;

	if (command->expanded)
		return ;
	command->expanded = 1;
	argv_vector = new_vector(20, sizeof(char **));
	free_tokens(command->redirections);
	splitted = split_quotes(command->cmd);
	command->redirections = extract_redirects(splitted);
	free_tokens(command->argv);
	command->argv = get_pure_tokens(splitted);
	free_tokens(splitted);
	expand_argv(command->argv, argv_vector);
	expand_redir(&(command->redirections));
	free_tokens(command->argv);
	command->argv = argv_vector->bytes;
	command->cmd = get_command_path(command->argv[0]);
	free(argv_vector);
	return ;
}
