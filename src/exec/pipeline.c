/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:24:21 by smaccary          #+#    #+#             */
/*   Updated: 2021/04/25 17:03:44 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parser.h"
#include "minishell.h"

int
	is_single_builtin(t_pipeline lst)
{
	t_command	*cmd;

	if (!lst || lst->next)
		return (0);
	cmd = lst->content;
   if (ft_strcmp(cmd->cmd, PARENTHESIS_OPEN))
		expand_command(cmd);
	//printf("here\n");
	//print_command(cmd);
	return (cmd && cmd->argv && cmd->argv[0] && is_builtin(cmd->argv[0]) != -1
	&& ft_strcmp(cmd->argv[0], PARENTHESIS_OPEN));
}

void
	wait_pipeline(t_pipeline pipeline)
{
	ft_lstiter(pipeline, (void *)wait_command);
}

int
	do_exec_pipeline(t_pipeline pipeline)
{
	pid_t	pid;
	int		status;

	pipe_nodes(pipeline);
	pid = exec_command_list(pipeline);
	waitpid(pid, &status, 0);
	wait_pipeline(pipeline);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	return (0);
}

int
	exec_single_builtin(t_command *cmd)
{
	extern	char	**environ;
	t_redirector	rdr;

	dup2_check(cmd->fd_input, 0);
	dup2_check(cmd->fd_output, 1);
	do_redirector(&rdr, cmd->redirections);
	exec_builtin(cmd->argv, environ);
	restore_streams(&rdr);
	g_exit_status = 0;
	return (g_exit_status);
}

int
	exec_pipeline(t_pipeline pipeline)
{
	pid_t			pid;
	int				status;

	if (check_pipeline(pipeline))
		return (1);
	if (is_single_builtin(pipeline))
		return (exec_single_builtin(pipeline->content));
	pipe_nodes(pipeline);
	print_pipeline(pipeline);
	signal(SIGINT, SIG_IGN);
	pid = exec_command_list(pipeline);
	waitpid(pid, &status, 0);
	wait_pipeline(pipeline);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	signal(SIGINT, (void *)interrupt_blank);
	return (g_exit_status);
}

int
	check_pipeline_run(char *condition, int last_return)
{
	if (condition == NULL || !strcmp(condition, SEMICOLON))
		return (1);
	if (!strcmp(condition, AND) && last_return == 0)
		return (1);
	if (!strcmp(condition, OR) && last_return != 0)
		return (1);
	return (0);
}
