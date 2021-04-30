/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:24:21 by smaccary          #+#    #+#             */
/*   Updated: 2021/04/30 14:49:35 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parser.h"
#include "minishell.h"

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
	signal(SIGQUIT, SIG_IGN);
	pid = exec_command_list(pipeline);
	waitpid(pid, &status, 0);
	wait_pipeline(pipeline);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	signal(SIGINT, (void *)interrupt_blank);
	signal(SIGQUIT, SIG_IGN);
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
