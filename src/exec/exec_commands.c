/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:42:25 by smaccary          #+#    #+#             */
/*   Updated: 2021/04/22 21:45:53 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "tokenizer.h"
#include "vector.h"

/*
void
	exec_parenthesis(t_command *cmd)
{
	int		pipes[2];
	pid_t	pid;
	int		status;

	pipe(pipes);
	write(pipes[1], cmd->cmd + 2, ft_strlen(cmd + 2) - 1);
	close(pipes[1]);
	pid = fork();
	if (pid == 0)
		exit(minishell());
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	return (g_exit_status);
	
}
*/

void
	clear_one_backslash(char *command)
{
	char	*line;
	char	*quote;

	line = command;
	quote = "\0";
	while (*line)
	{
		if (!*quote && ft_strchr("\"'", *line))
			quote = line;
		if ((!*quote || *quote == '"') && line[0] == '\\')
		{
			if (line[1] == '\\')
			{
				ft_memmove(line, line + 1, ft_strlen(line));
				++line;
			}
			else if (!*quote && !ft_strchr("\"'", line[1]))
				ft_memmove(line, line + 1, ft_strlen(line));
		}
		++line;
		if (*line == *quote)
			quote = "\0";
	}
}

void
	clear_escaped_quotes(char *command)
{
	char	*line;

	line = command;
	while (*line)
	{
		if (line[0] == '\\' && line[1] && ft_strchr("\"'", line[1]))
			ft_memmove(line, line + 1, ft_strlen(line));
		++line;
	}
}
void
	clean_argv_backslashes(char **commands)
{
	iter_argv(commands, (void *)clear_one_backslash);
}

int
	exec_parenthesis(t_command *cmd)
{
	extern char	**environ;

	redirect_command(cmd);
	return (builtin_parenthesis(cmd->argv, environ));
}

int
	is_cmd_parenthesis(t_command *cmd)
{
	return (!ft_strcmp(PARENTHESIS_OPEN, cmd->cmd));
}

void
	expand_argv(char *argv, t_vector *new)
{
	char	**current;
	char	*expanded;
	char	*dequoted;
	char	**splitted;

	//printf("argv: %s\n", argv);
	expanded = perform_expansions(argv);
	//printf("expanded: %s\n", expanded);
	splitted = split_quotes(expanded);
//	print_argv(splitted);
	clean_argv_backslashes(splitted);
//	print_argv(splitted);
	free(expanded);
	current = splitted;
//	print_argv(splitted);
	while (*current)
	{
		//printf("current: %s\n", *current);
		dequoted = remove_quotes(*current);
		//printf("dequoted: %s\n", dequoted);
		//clear_one_backslash(dequoted);
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

char
	*get_next_token(char *str)
{
	static char	*current = NULL;
	static char	*start = NULL;
	char		*begin;
	char		*quote;
	int			skip;

	if (start != str)
	{
		start = str;
		current = str;
	}
//	printf("str: %s\n", str);
	skip = 0;
	while (ft_isspace(*current) || (*current == '\\' && ft_isspace(current[1])))
		current++;
	if (!*current)
		return (NULL);
	begin = current;
	while (*current && !ft_isspace(*current))
	{
		if (ft_strchr("\"'", *current))
		{
			quote = current;
			current++;
			while (*current != *quote || skip)
			{
				skip = 0;
				if (*current == 0)
					return (NULL);
				if (current[0] == '\\' && current[1] == '\\')
					current += 2;
				else
				{
					skip = (*quote != '\'' && *current == '\\'
							&& current[1] == *quote);
					current++;				
				}
			}
			current++;
		}
		while (*current && (skip || !ft_strchr("\"' ", *current)))
		{
			skip = (*current == '\\' && ft_strchr("\"' ", current[1]));
			current++;
		}
	}
	return (ft_strndup(begin, current - begin));
}

char
	**split_quotes(char	*str)
{
	t_vector	*v;
	char		*current;
	char		*new_token;
	char		**splitted;

	current = str;
	v = new_vector(10, sizeof(char **));
	while ((new_token = get_next_token(str)))
		vector_append(v, &new_token, 1);
	splitted = v->bytes;
	//print_argv(splitted);
	//clean_argv_backslashes(splitted);
	//print_argv(splitted);
	free(v);
	return (splitted);
	
}

void
	expand_redir(char ***redir_ptr, t_vector *argv_vect)
{
	char		**current;
	char		**tokenized;
	char		*expanded;
	char		*dequoted;
	t_vector	*redir_vector;

	current = *redir_ptr;
	redir_vector = new_vector(4, sizeof(char **));
	while (*current)
	{
		if (is_redirect(*current))
		{
			tokenized = split_quotes(current[1]);
			extract_redir_tokens(tokenized + 1, argv_vect);
			if (!tokenized[0])
				break ;
			expanded = perform_expansions(tokenized[0]);
			dequoted = remove_quotes(expanded);
			free(expanded);
			vector_append(redir_vector, current, 1);
			vector_append(redir_vector, &dequoted, 1);
			current++;
		}
		else
			expand_argv(*current, argv_vect);
		current++;
	}
	vector_append(redir_vector, current, 1);
	free(*redir_ptr);
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
	//print_argv(command->argv);
	iter_argv(command->argv, (void *)clear_escaped_quotes);
//	clean_argv_backslashes(command->argv);
	command->cmd = get_command_path(command->argv[0]);
	//print_command(command);
	free(v);
	return ;
}

void
	exec_command(t_command *command)
{
	extern char		**environ;

	//if (!strcmp(command->cmd, ESCAPE))
	if (is_cmd_parenthesis(command))
		exit(exec_parenthesis(command));
	expand_command(command);
	redirect_command(command);
	if(!command->cmd)
		exit(0);
	else if (is_builtin(command->argv[0]) != -1)
		exit(exec_builtin(command->argv, environ));
	else
		execve(command->cmd, command->argv, environ);
	pcmd_not_found(command);
	free_cmd(command);
	exit(127);
}

int
	exec_command_list(t_list *commands)
{
	t_list		*current;
	t_command	*cmd;

	current = commands;
	while (current)
	{
		cmd = current->content;
		cmd->pid = fork();
		if (cmd->pid == 0)
		{
			close_all_cmds(commands, cmd);
			exec_command(cmd);
		}
		current = current->next;
	}
	close_all_cmds(commands, NULL);
	return (0);
}

void
	wait_command(t_command *cmd)
{
	waitpid(cmd->pid, NULL, 0);
}
