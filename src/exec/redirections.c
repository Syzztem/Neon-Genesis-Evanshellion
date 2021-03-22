/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:30:00 by smaccary          #+#    #+#             */
/*   Updated: 2021/03/22 13:33:05 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void
	close_checked(int fd)
{
	if (fd != 0 && fd != 1)
		close (fd);
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

void
	restore_streams(t_redirector *rdr)
{
	if (rdr->stdout_dup > 0)
		dup2_check(rdr->stdout_dup, 1);
	if (rdr->stdin_dup > 0)
		dup2_check(rdr->stdin_dup, 0);
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
	redirects_to_fds(rdr->rtokens, &rdr->in_fd, &rdr->out_fd);
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
