/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:09:23 by smaccary          #+#    #+#             */
/*   Updated: 2021/03/29 14:00:51 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "exec.h"

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

/*
int
	open_input(char	**input_path_ptr)
{
	size_t	redir_type;
	int		fd;

	redir_type = ft_strlen(*input_path_ptr);
	if (redir_type == 1)
	{
		fd = open(input_path_ptr[1], O_RDONLY);
		if (fd < 0)
			printf("%s : %s: %s\n", SHELL_NAME, strerror(errno),
			input_path_ptr[1]);
	}
	else if (redir_type == 2)
	{
		
	}
}*/