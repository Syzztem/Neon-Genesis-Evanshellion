/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:30:00 by smaccary          #+#    #+#             */
/*   Updated: 2021/05/11 01:25:17 by root             ###   ########.fr       */
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

int
	abort_redirections(char **redirection, int *in_fd, int *out_fd)
{
	close_checked(*in_fd);
	close_checked(*out_fd);
	*in_fd = -1;
	*out_fd = -1;
	psyntax_error(redirection[0]);
	g_exit_status = 2;
	return (-1);
}

int
	create_files(char **redirections, int *in_fd, int *out_fd)
{
	char	**current;
	int		fd;

	current = redirections;
	while (*current)
	{
		if (tab_find_last_token(current, redirects()))
		{
			if (current[1] == NULL || current[1][0] == 0)
				return (abort_redirections(current, in_fd, out_fd));
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
	return (0);
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
	if (create_files(redirections, &rdr->in_fd, &rdr->out_fd) < 0)
		return (-1);
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
