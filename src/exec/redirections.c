/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:30:00 by smaccary          #+#    #+#             */
/*   Updated: 2021/05/09 00:01:45 by user42           ###   ########.fr       */
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

int
	do_redirector(t_redirector *rdr, char **redirections)
{
	rdr->in_fd = 0;
	rdr->out_fd = 1;
	rdr->rtokens = redirections;
	rdr->stdin_dup = -1;
	rdr->stdout_dup = -1;
	if (!redirections || !*redirections)
		return (0);
	create_files(redirections, &rdr->in_fd, &rdr->out_fd);
	if (rdr->in_fd < 0 || rdr->out_fd < 0)
		return (-1);
	rdr->stdin_dup = dup(0);
	rdr->stdout_dup = dup(1);
	dup2_check(rdr->in_fd, 0);
	dup2_check(rdr->out_fd, 1);
	return (0);
}

int
	redirect_command(t_command *cmd)
{
	t_redirector	rdr;

	dup2_check(cmd->fd_input, 0);
	dup2_check(cmd->fd_output, 1);
	return (do_redirector(&rdr, cmd->redirections));
}
