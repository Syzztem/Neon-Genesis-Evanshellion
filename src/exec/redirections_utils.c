/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:09:23 by smaccary          #+#    #+#             */
/*   Updated: 2021/04/29 20:53:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "exec.h"
#include "get_next_line.h"

void
	close_checked(int fd)
{
	if (fd != 0 && fd != 1)
		close(fd);
}

void
	dup2_check(int fd_src, int fd_dst)
{
	if (fd_src != fd_dst && fd_dst >= 0)
	{
		dup2(fd_src, fd_dst);
		close(fd_src);
	}
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
	redir_type = ft_strcmp(*output_path_ptr, REDIR_REPLACE);
	if (!redir_type)
		open_mode |= O_TRUNC;
	else
		open_mode |= O_APPEND;
	return (open(output_path_ptr[1], open_mode, open_flags));
}

int
	open_input(char **input_path_ptr)
{
	int	redir_type;
	int	fd;

	redir_type = ft_strcmp(input_path_ptr[0], REDIR_INPUT);
	if (!redir_type)
	{
		fd = open(input_path_ptr[1], O_RDONLY);
		if (fd < 0)
			printf("%s : %s: %s\n", SHELL_NAME, strerror(errno),
			input_path_ptr[1]);
		return (fd);
	}
	return (here_doc(input_path_ptr[1]));
}

int
	open_redir(char **redir)
{
	char	type;

	type = redir[0][0];
	if (type == '>')
		return (open_output(redir));
	else if (type == '<')
		return (open_input(redir));
	return (-1);
}
