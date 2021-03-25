/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:01:45 by smaccary          #+#    #+#             */
/*   Updated: 2021/03/24 16:31:42 by smaccary         ###   ########.fr       */
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
	cmd->sep = sep;
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

	if (tokens != tokens_start)
	{
		tokens_start = tokens;
		current = tokens;
	}
	if (current == NULL || *current == NULL)
		return (NULL);
	end = get_command_len(current);
	command = command_from_tokens(dup_n_tab(current, end), *find_sep(current));
	current += end;
	if (*current)
		current++;
	return (command);
}
