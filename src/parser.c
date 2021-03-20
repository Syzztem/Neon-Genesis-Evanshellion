/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 13:16:41 by smaccary          #+#    #+#             */
/*   Updated: 2021/03/20 20:04:40 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
#include <limits.h>

t_command
	*new_command(char *cmd, char **argv, char *sep)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
	*new = (t_command){
	.cmd = cmd,
	.argv = argv,
	.sep = sep,
	.fd_output = 1,
	.fd_input =  0,
	.pid =  -1};
	return (new);
}

char
	*alloc_path_buf(char *cmd)
{
	(void)cmd;
	return (ft_calloc(PATH_MAX + 1, 1));
}

t_command
	*init_command_from_tokens(char **tokens, char *sep)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	cmd->sep = sep;
	cmd->tokens = dup_tab(tokens);
	cmd->redirections = extract_redirects(tokens);
	cmd->argv = get_pure_tokens(tokens);
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
	path_buf = alloc_path_buf(tokens[0]);// I can't exactly know the size of the command's path in advance so i I have to alloc the maximum size possible to avoid buffer overflow :(
	found_exec = find_exec(path_buf, tokens[0]);
	if (!path_buf || !found_exec)
	{
		free(path_buf);
		cmd->cmd = ft_strdup(cmd->tokens[0]);
		return (cmd);
	}
	if (found_exec == tokens[0])
		ft_strlcpy(path_buf, tokens[0], PATH_MAX);
	cmd->cmd = path_buf;
	return(cmd);
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
//	printf("len %d\n", end);
	command = command_from_tokens(dup_n_tab(current, end), *find_sep(current));
	current += end;
	if (*current)
		current++;
	return (command);
}


t_ast_node
	*node_from_line(char **abstract_pipeline, char *sep)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	node->abstract_pipeline = abstract_pipeline;
	node->sep = sep;
	return (node);
}


t_ast_node
	*get_next_ast_node(char **tokens)
{
	static char	**current = NULL;
	static char **tokens_start = NULL;
	int			end;
	t_ast_node	*node;

	if (tokens != tokens_start)
	{
		tokens_start = tokens;
		current = tokens;
	}
	if (current == NULL || *current == NULL)
		return (NULL);
	end = get_pipeline_len(current);
	node = node_from_line(dup_n_tab(current, end), *find_token_in_tokens(current, PIPELINE_SEPARATORS));
	current += end;
	if (*current)
		current++;
	return (node);
}

t_ast
	parse_ast(char **tokens)
{
	t_ast_node	*node;
	t_list		*lst;
	
	lst = NULL;
	while ((node = get_next_ast_node(tokens)))
		ft_lstadd_back(&lst, node);
	get_next_ast_node(NULL);
	return (lst);
}

t_pipeline
	parse_pipeline(char **tokens)
{
	t_command	*command;
	t_list		*lst;
	
	lst = NULL;
	while ((command = get_next_command(tokens)))
		ft_lstadd_back(&lst, command);
	get_next_command(NULL);
	return (lst);
}

/*
int	fork_pipes (int n, t_command *cmd)
{
  int	i;
  pid_t	pid;
  int	in;
  int	fd [2];

  in = 0;
  for (i = 0; i < n - 1; ++i)
    {
      pipe(fd);
      spawn_proc (in, fd [1], cmd + i);
      close (fd [1]);
      in = fd [0];
    }

  if (in != 0)
    dup2 (in, 0);

  return execve (cmd[i].argv [0], (char * const *)cmd[i].argv);
}
*/

/*
int main(void)
{
	char *tokens[] = {NULL};

	printf("len:%d\n", tokens_len(tokens));
	return (0);
}
*/



int
	is_redirect(char *token)
{
	return ((int)find_token(token, REDIRECTS));
}

size_t
	count_avoided_tokens(char **tokens)
{
	size_t	count;

	count = 0;
	while (*tokens)
	{
		if (is_redirect(*tokens))
			count += 2;
		tokens++;
	}
	return (count);
}

/*
** Extracts redirections and their arguments and returns them in a char **
** -> {">", "arg1", "<", "arg2", ">>", "arg3"} 
*/

char
	**extract_redirects(char **tokens)
{
	char	**extracted;
	size_t	i;

	i = 0;
	extracted = ft_calloc(count_avoided_tokens(tokens) + 1, sizeof(char *));
	if (!extracted)
		return (NULL);
	while (*tokens)
	{
		if (is_redirect(*tokens))
		{
			extracted[i] = *tokens;
			if (*(tokens + 1))
				extracted[++i] = *(++tokens);
			i++;
		}
		tokens++;
	}
	return (extracted);
}

size_t
	pure_tokens_len(char **tokens, char **excluded_tokens)
{
	char	**current;
	size_t	len;

	current = tokens;
	len = 0;
	while (*current)
	{
		if (find_token(*current, excluded_tokens) == 0)
			len++;
		current++;
	}
	return (len);
}

char
	**ref_in_tokens(char *ref, char **tokens)
{
	while (*tokens)
	{
		if (ref == *tokens)
			return (tokens);
		tokens++;
	}
	return (NULL);		
}

/*
** Return tokens without redirections and their arguments 
*/

char
	**get_pure_tokens(char **tokens)
{
	char	**pure_tokens;
	char	**extracted;
	char	**current;
	size_t	i;

	i = 0;
	current = tokens;
	extracted = extract_redirects(tokens);
	pure_tokens = ft_calloc(pure_tokens_len(tokens, extracted) + 1, sizeof(char *));
	while (*current)
	{
		if (ref_in_tokens(*current, extracted) == 0)
		{
			pure_tokens[i] = *current;
			i++;
		}
		current++;
	}
	return (pure_tokens);
}

int
	check_path_ptr(char **path_ptr)
{
	return (path_ptr && *path_ptr && path_ptr[1] && !is_sep(path_ptr[1]));
}


int
	open_output(char **output_path_ptr)
{
	int	open_mode;
	int	redir_type;
	int open_flags;

	redir_type = 0;
	open_flags = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	open_mode = O_WRONLY | O_CREAT;
	redir_type |= (int)ft_strlen(*output_path_ptr);
	if (redir_type == 1)
		open_mode |= O_TRUNC;
	else if (redir_type == 2)
		open_mode |= O_APPEND;
	return (open(output_path_ptr[1], open_mode, open_flags));
}

/*
** Parse redirects tokens, opens files and assign them accordingly to fd_input/output ( input : "<", output: ">") 
** Returns redirection status as a binary mask (replace = 001 | append = 010 | input = 100)
*/

int
	redirects_to_fds(char **redirects, int *fd_input, int *fd_output)
{
	char	**input_path_ptr;
	char	**output_path_ptr;
	int		open_mode;

	output_path_ptr = tab_find_last_token(OUTPUT_REDIRECTS, redirects);
	open_mode = O_WRONLY | O_CREAT;
	if (check_path_ptr(output_path_ptr))
		*fd_output = open_output(output_path_ptr);
	input_path_ptr = tab_find_last_token(INPUT_REDIRECTS, redirects);
	if (check_path_ptr(input_path_ptr))
	{
		*fd_input = open(input_path_ptr[1], O_RDONLY);
		if (*fd_input < 0)
			printf("%s : %s: %s\n", SHELL_NAME, strerror(errno), input_path_ptr[1]);
	}
	return (0);
}
