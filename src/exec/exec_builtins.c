/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 20:55:13 by user42            #+#    #+#             */
/*   Updated: 2021/05/08 15:12:31 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "exec.h"

int
	is_single_builtin(t_pipeline lst)
{
	t_command	*cmd;

	if (!lst || lst->next)
		return (0);
	cmd = lst->content;
	if (ft_strcmp(cmd->cmd, PARENTHESIS_OPEN))
		expand_command(cmd);
	return (cmd && cmd->argv && cmd->argv[0] && is_builtin(cmd->argv[0]) != -1
	&& ft_strcmp(cmd->argv[0], PARENTHESIS_OPEN));
}

int
	exec_single_builtin(t_command *cmd)
{
	extern	char	**environ;
	t_redirector	rdr;

	dup2_check(cmd->fd_input, 0);
	dup2_check(cmd->fd_output, 1);
	if (do_redirector(&rdr, cmd->redirections) < 0)
		return (errno);
	exec_builtin(cmd->argv, environ);
	restore_streams(&rdr);
	g_exit_status = 0;
	return (g_exit_status);
}
