/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 15:15:38 by smaccary          #+#    #+#             */
/*   Updated: 2021/04/29 20:48:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

void
	pesc(char *token, int fd)
{
	ft_putstr_fd("\"", fd);
	if (!token)
	{
		ft_putstr_fd("(null)", fd);
	}
	else
	{
		while (*token)
		{
			if (*token == ESCAPE_CHAR)
			{
				if (DEBUG_SEP)
					ft_putstr_fd("\\x1b", fd);
			}
			else
				ft_putchar_fd(*token, fd);
			token++;
		}
	}
	ft_putstr_fd("\"", fd);
}

int
	print_argv(char **argv)
{
	printf("%p -> ", argv);
	if (argv)
	{
		printf("%s", "{");
		while (0[argv])
		{
			pesc(*argv, 1);
			printf("%s", ", ");
			fflush(stdout);
			argv++;
		}
		printf("%s", "NULL};\n");
	}
	else
		printf("%s\n", "(null)");
	fflush(stdout);
	return (0);
}

void
	print_command(t_command *command)
{
	if (!DEBUG)
		return ;
	printf("%p:\n", command);
	if (command)
	{
		printf("  - %-15s", "cmd:");
		pesc(command->cmd, 1);
		ft_putstr_fd("\n", 1);
		printf("  - %-15s", "argv:");
		print_argv(command->argv);
		printf("  - %-15s", "tokens:");
		print_argv(command->tokens);
		printf("  - %-15s", "redirections:");
		print_argv(command->redirections);
		printf("  - %-15s", "sep:");
		pesc(command->sep, 1);
		write(1, "\n", 1);
		printf("  - %-15s%d\n  - %-15s%d\n", "input:", command->fd_input,
				"output:", command->fd_output);
		printf("  - %-15s%d\n\n", "pid:", command->pid);
	}
	fflush(stdout);
}

void
	print_pipeline(t_pipeline lst)
{
	if (!DEBUG)
		return ;
	ft_lstiter(lst, (void *)print_command);
}

/*
**	For testing purposes only
*/

char
	*do_find_exec(char *cmd)
{
	char	*path_buf;

	path_buf = alloc_path_buf(cmd);
	if (!path_buf || !find_exec(path_buf, cmd))
	{
		free(path_buf);
		return (ft_strdup(cmd));
	}
	return (path_buf);
}

/*
**	For testing purposes only
*/

void
	print_exec_path(char *cmd)
{
	char	*path;

	path = do_find_exec(cmd);
	printf("%s -> %s\n", cmd, path);
}

void
	iter_argv(char **argv, void (*func)(char *))
{
	char **current;

	current = argv;
	while (*current)
	{
		func(*current);
		current++;
	}
}

void
	print_ast_node(t_ast_node *node)
{
	if (!DEBUG && !DEBUG_AST)
		return ;
	printf("  node: %p\n", node);
	printf("    - %-15s", "pipeline:");
	print_argv(node->abstract_pipeline);
	puts("");
	print_pipeline(node->pipeline);
	printf("    - %-15s", "sep:");
	pesc(node->sep, 1);
	puts("");
}

void
	print_ast(t_ast ast)
{
	if (!DEBUG && !DEBUG_AST)
		return ;
	printf("ast: %p\n", ast);
	ft_lstiter(ast, (void *)print_ast_node);
	puts("");
}