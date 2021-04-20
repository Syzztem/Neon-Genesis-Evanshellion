/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:42:25 by smaccary          #+#    #+#             */
/*   Updated: 2021/04/21 00:24:54 by root             ###   ########.fr       */
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

int
	exec_parenthesis(t_command *cmd)
{
	return (exec_line(cmd->argv));
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

	expanded = perform_expansions(argv);
	splitted = tokenize(expanded);
	current = splitted;
	while (*current)
	{
		dequoted = remove_quotes(*current);
		vector_append(new, &dequoted, 1);
		current++;
	}
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
	int			skip;

	if (start != str)
	{
		start = str;
		current = str;
	}
	skip = 0;
	while (ft_isspace(*current))
		current++;
	if (!*current)
		return (NULL);
	if (ft_strchr("\"'", *current))
	{
		begin = current;
		current++;
		while (*current != *begin || skip)
		{
			skip = 0;
			if (*current == 0)
				return (NULL);
			if (*current == '\\' && current[1] == *begin)
				skip = 1;
			current++;
		}
		current++;
		return (ft_strndup(begin, current - begin));
	}
	begin = current;
	while (*current && (skip || !ft_strchr("\"' ", *current)))
	{
		if (*current == '\\' && ft_strchr("\"' ", current[1]))
			skip = 1;
		current++;
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
			printf("string: %s\ntokenized: ", current[1]);
			//tokenized = tokenize(current[1]);
			tokenized = split_quotes(current[1]);
			print_argv(tokenized);
			printf("\n");
			extract_redir_tokens(tokenized + 1, argv_vect);
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
	free(*redir_ptr);
	*redir_ptr = redir_vector->bytes;
	free(redir_vector);
}

void
	expand_command(t_command *command)
{
	char		**tokenized;
	t_vector	*v;

	v = new_vector(20, sizeof(char **));
	expand_argv(command->cmd, v);
	expand_redir(&(command->redirections), v);
	command->argv = v->bytes;
	command->cmd = get_command_path(command->argv[0]);
	print_command(command);
	return ;
}

void
	exec_command(t_command *command)
{
	extern char		**environ;

	expand_command(command);
	redirect_command(command);
	//if (!strcmp(command->cmd, ESCAPE))
	if(!command->cmd)
		exit(0);
	if (is_cmd_parenthesis(command))
		exit(exec_parenthesis(command));
	else if (is_builtin(command->argv[0]) != -1)
		exit(exec_builtin(command->argv, environ));
	else
		execve(command->cmd, command->argv, environ);
	pcmd_not_found(command);
	exit(errno);
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
