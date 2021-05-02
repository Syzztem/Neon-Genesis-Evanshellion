/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 15:15:38 by smaccary          #+#    #+#             */
/*   Updated: 2021/05/02 10:25:39 by root             ###   ########.fr       */
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
			printf("\"%s\"", *argv);
			printf("%s", ", ");
			argv++;
		}
		printf("%s", "NULL};\n");
		fflush(stdout);
	}
	else
		printf("%s\n", "(null)");
	fflush(stdout);
	return (0);
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
