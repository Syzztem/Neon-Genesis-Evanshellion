/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:01:45 by smaccary          #+#    #+#             */
/*   Updated: 2021/05/10 23:53:35 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

t_command
	*new_command(char *cmd, char **argv, char *sep)
{
	t_command	*new;

	new = ft_calloc(1, sizeof(t_command));
	if (!new)
		return (NULL);
	*new = (t_command){
	.cmd = cmd,
	.argv = argv,
	.sep = sep,
	.fd_output = 1,
	.fd_input = 0,
	.pid = -1};
	return (new);
}

t_command
	*command_from_tokens(char **tokens, char *sep)
{
	t_command	*cmd;
	char		**extracted;

	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (NULL);
	if (sep)
		cmd->sep = ft_strdup(sep);
	else
		cmd->sep = NULL;
	cmd->tokens = dup_tab(tokens);
	extracted = extract_redirects(tokens);
	cmd->redirections = dup_tab(extracted);
	free_tokens(extracted);
	cmd->argv = get_pure_tokens(tokens);
	if (cmd->argv[0] == NULL)
		cmd->argv[0] = ft_strdup("");
	cmd->cmd = cmd->argv[0];
	cmd->fd_input = 0;
	cmd->fd_output = 1;
	cmd->pid = -1;
	return (cmd);
}

char
	*get_command_path(char *cmd)
{
	char		*path_buf;
	char		*found_exec;

	if (!cmd)
		return (NULL);
	path_buf = alloc_path_buf(cmd);
	found_exec = find_exec(path_buf, cmd);
	if (!path_buf || !found_exec)
	{
		free(path_buf);
		return (ft_strdup(cmd));
	}
	if (found_exec == cmd)
		ft_strlcpy(path_buf, cmd, PATH_MAX);
	return (path_buf);
}

t_command
	*parse_simple_command(char **current, size_t *len_ptr)
{
	size_t		end;
	char		**extracted;
	t_command	*command;

	end = get_command_len(current);
	extracted = dup_n_tab(current, end);
	command = command_from_tokens(extracted, *find_sep(current));
	//print_command(command);
	free_tokens(extracted);
	if (len_ptr)
		*len_ptr = end;
	return (command);
}

t_command
	*get_next_command(char **tokens)
{
	static char	**current = NULL;
	static char **tokens_start = NULL;
	size_t		end;
	t_command	*command;

	if (tokens != tokens_start)
	{
		tokens_start = tokens;
		current = tokens;
	}
	if (current == NULL || *current == NULL)
		return (NULL);
	if (!ft_strcmp(*current, PARENTHESIS_OPEN))
		command = parse_parenthesis(current, &end);
	else
		command = parse_simple_command(current, &end);
	current += end;
	if (*current)
		current++;
	return (command);
}
