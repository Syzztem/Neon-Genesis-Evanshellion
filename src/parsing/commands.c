/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:01:45 by smaccary          #+#    #+#             */
/*   Updated: 2021/04/28 23:24:48 by root             ###   ########.fr       */
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
	*command_from_tokens(char **tokens, char *sep)
{

	t_command	*cmd;

	cmd = init_command_from_tokens(tokens, sep);
	/*if (cmd)
		cmd->cmd = get_command_path(cmd->cmd);*/
	return (cmd);
}

t_command
	*parse_simple_command(char **current, size_t *len_ptr)
{
	size_t		end;
	char		**extracted;
	t_command	*command;

	end = get_command_len(current);
	extracted = dup_n_tab(current, end);
	PARGV(extracted);
	command = command_from_tokens(extracted, *find_sep(current));
	print_command(command);
	free_tokens(extracted);
	if (len_ptr)
		*len_ptr = end;
	return (command);
}

size_t
	parenthesis_len(char **tokens)
{
	char		**current;
	unsigned	level;

	if (!tokens || !*tokens)
		return (1);
	current = tokens + 1;
	level = 1;
	//printf("%s\n", *tokens);
	while (*current && level)
	{
		if (!ft_strcmp(*current, PARENTHESIS_OPEN))
			++level;
		if (!ft_strcmp(*current, PARENTHESIS_CLOSE))
			--level;
		current++;
	}
	if (level)
	{
		ft_putendl_fd(SHELL_NAME ": missing matching `)'", 2);
		PARGV(tokens);
		return (0);
	}
	return (current - tokens);
}

t_command
	*parse_parenthesis(char **current, size_t *len_ptr)
{
	size_t		end;
	char		**extracted;
	t_command	*command;

	PARGV(current);
	end = parenthesis_len(current);
	if (end == 0)
	{
		printf("RETURNING NULL\n");
		return (NULL);
	}
	//printf("end: %d\n", end);
	extracted = dup_n_tab(current, end);
	command = new_command(ft_strdup(extracted[0]), extracted, NULL);
	//command->tokens = current;
	command->redirections = extract_redirects(current + end);
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
	PARGV(current);
	if (current == NULL || *current == NULL)
		return (NULL);
	//printf("tokens: ");
	//print_argv(tokens);
	if (!strcmp(*current, PARENTHESIS_OPEN))
	{
		//printf("hello: ");
		//print_argv(current);
		//printf("\n");
		command = parse_parenthesis(current, &end);
	}
	else
		command = parse_simple_command(current, &end);
	current += end;
	if (*current)
		current++;
	//printf("end next\n");
	//print_argv(current);
	return (command);
}
