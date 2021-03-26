/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:01:45 by smaccary          #+#    #+#             */
/*   Updated: 2021/03/25 20:01:35 by root             ###   ########.fr       */
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
	*init_command_from_tokens(char **tokens, char *sep)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (NULL);
	if (sep)
		cmd->sep = ft_strdup(sep);
	else
		cmd->sep = NULL;
	cmd->tokens = dup_tab(tokens);
	cmd->redirections = extract_redirects(tokens);
	cmd->argv = get_pure_tokens(tokens);
	cmd->cmd = cmd->argv[0];
	cmd->fd_input = 0;
	cmd->fd_output = 1;
	cmd->pid = -1;
	return (cmd);
}

t_command
	*command_from_tokens(char **tokens, char *sep)
{
	char		*path_buf;
	char		*found_exec;
	t_command	*cmd;

	cmd = init_command_from_tokens(tokens, sep);
	if (!cmd)
		return (NULL);
	path_buf = alloc_path_buf(cmd->cmd);
	found_exec = find_exec(path_buf, cmd->cmd);
	if (!path_buf || !found_exec)
	{
		free(path_buf);
		return (cmd);
	}
	if (found_exec == cmd->cmd)
		ft_strlcpy(path_buf, cmd->cmd, PATH_MAX);
	cmd->cmd = path_buf;
	return (cmd);
}

t_command
	*get_next_command(char **tokens)
{
	static char	**current = NULL;
	static char **tokens_start = NULL;
	int			end;
	t_command	*command;
	char		**extracted;

	if (tokens != tokens_start)
	{
		tokens_start = tokens;
		current = tokens;
	}
	if (current == NULL || *current == NULL)
		return (NULL);
	end = get_command_len(current);
	extracted = dup_n_tab(current, end);
	command = command_from_tokens(extracted, *find_sep(current));
	free_tokens(extracted);
	current += end;
	if (*current)
		current++;
	return (command);
}
