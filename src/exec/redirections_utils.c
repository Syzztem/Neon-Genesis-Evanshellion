/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:09:23 by smaccary          #+#    #+#             */
/*   Updated: 2021/04/29 00:10:12 by root             ###   ########.fr       */
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
	here_doc(char *end_mark)
{
	int		pipes[2];
	char	*line;
	
	pipe(pipes);
	//printf("HERE DOC: %s\n", end_mark);
	if (is_shell_interactive())
			ft_putstr_fd("> ", 2);
	while (get_next_line(0, &line) == 1 && line && strcmp(line, end_mark))
	{
		write(pipes[1], line, ft_strlen(line));
		write(pipes[1], "\n", 1);
		free(line);
		if (is_shell_interactive())
			ft_putstr_fd("> ", 2);
	}
	close(pipes[1]);
	return (pipes[0]);
}

int
	open_input(char	**input_path_ptr)
{
	int	redir_type;
	int		fd;

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
	open_redir(char	**redir)
{
	char	type;
	
	type = redir[0][0];
	if (type == '>')
		return (open_output(redir));
	else if (type == '<')
		return (open_input(redir));
	return (-1);
}