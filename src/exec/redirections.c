/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:30:00 by smaccary          #+#    #+#             */
/*   Updated: 2021/05/04 18:48:54 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void
	restore_streams(t_redirector *rdr)
{
	if (rdr->stdout_dup > 0)
		dup2_check(rdr->stdout_dup, 1);
	if (rdr->stdin_dup > 0)
		dup2_check(rdr->stdin_dup, 0);
}

void
	create_files(char **redirections, int *in_fd, int *out_fd)
{
	char	**current;
	int		fd;

	current = redirections;
	while (*current)
	{
		if (tab_find_last_token(current, redirects()))
		{
			fd = open_redir(current);
			if (**current == '<')
			{
				close_checked(*in_fd);
				*in_fd = fd;
			}
			else
			{
				close_checked(*out_fd);
				*out_fd = fd;
			}
		}
		current++;
	}
}

void
	do_redirector(t_redirector *rdr, char **redirections)
{
	rdr->in_fd = 0;
	rdr->out_fd = 1;
	rdr->rtokens = redirections;
	rdr->stdin_dup = -1;
	rdr->stdout_dup = -1;
	if (!redirections || !*redirections)
		return ;
	create_files(redirections, &rdr->in_fd, &rdr->out_fd);
	rdr->stdin_dup = dup(0);
	rdr->stdout_dup = dup(1);
	dup2_check(rdr->in_fd, 0);
	dup2_check(rdr->out_fd, 1);
}

void
	redirect_command(t_command *cmd)
{
	t_redirector	rdr;

	dup2_check(cmd->fd_input, 0);
	dup2_check(cmd->fd_output, 1);
	do_redirector(&rdr, cmd->redirections);
}

/*
** Parse redirects tokens, opens files and assign them accordingly to
** fd_input/output ( input : "<", output: ">")
** Returns redirection status as a binary mask
** (replace = 001 | append = 010 | input = 100)
*/

int
	redirects_to_fds(char **redirects, int *fd_input, int *fd_output)
{
	char	**input_path_ptr;
	char	**output_path_ptr;
	int		open_mode;

	output_path_ptr = tab_find_last_token(output_redirects(), redirects);
	open_mode = O_WRONLY | O_CREAT;
	if (check_path_ptr(output_path_ptr))
		*fd_output = open_output(output_path_ptr);
	input_path_ptr = tab_find_last_token(input_redirects(), redirects);
	if (check_path_ptr(input_path_ptr))
	{
		*fd_input = open_input(input_path_ptr);
		if (*fd_input < 0)
			printf("%s : %s: %s\n", SHELL_NAME, strerror(errno),
			input_path_ptr[1]);
	}
	return (0);
}
