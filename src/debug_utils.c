/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 15:15:38 by smaccary          #+#    #+#             */
/*   Updated: 2021/02/27 12:01:53 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int
	print_argv(char **argv)
{
	if (!DEBUG)
		return (0);
	printf("%p -> ", argv);
	if (argv && *argv)
	{
		printf("%s", "{");
		while (*argv)
		{
			printf("\"%s\"", *argv);
			argv++;
			if (*argv)
				printf("%s", ", ");
		}
		printf("%s", "}\n");
	}	
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
		printf("  - %-10s\"%s\"\n", "cmd:", command->cmd);
		printf("  - %-10s", "argv:");
		print_argv(command->argv);
		printf("  - %-10s%d\n  - %-10s%d\n", "input:", command->fd_input, "output:", command->fd_output);
		printf("  - %-10s\"%s\"\n\n", "sep:", command->sep);
	}
	fflush(stdout);
}

void
	print_cmd_lst(t_list *lst)
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
