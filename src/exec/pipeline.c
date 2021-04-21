/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:24:21 by smaccary          #+#    #+#             */
/*   Updated: 2021/04/21 02:14:58 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int
	is_single_builtin(t_pipeline lst)
{
	t_command	*cmd;

	if (!lst || lst->next)
		return (0);
	cmd = lst->content;
	return (cmd && cmd->argv && is_builtin(cmd->argv[0]) != -1
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
	//print_pipeline(pipeline);
	pid = exec_command_list(pipeline);
	waitpid(pid, &status, 0);
	wait_pipeline(pipeline);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	return (0);
}

/*
int
	exec_abstract_pipeline(char *tokens)
{
	t_pipeline		pipeline;
	extern	char	**environ;
	t_redirector	rdr;

	pipeline = parse_pipeline(tokens);
	if (check_pipeline(pipeline))
	{
		printf("pipeline err\n");
		exit(1);
	}
	if (is_single_builtin(pipeline))
	{
		do_redirector(&rdr, ((t_command *)pipeline->content)->redirections);
		exec_builtin(((t_command *)pipeline->content)->argv, environ);
		restore_streams(&rdr);
	}
	else
		exec_pipeline(pipeline);
	free_pipeline(&pipeline);
	return (g_exit_status);
}
*/


int
	exec_pipeline(t_pipeline pipeline)
{
	extern	char	**environ;
//	t_redirector	rdr;
	pid_t			pid;
	int				status;

	if (check_pipeline(pipeline))
	{
		printf("pipeline err\n");
		exit(1);
	}
	/*if (is_single_builtin(pipeline))
	{
		do_redirector(&rdr, ((t_command *)pipeline->content)->redirections);
		exec_builtin(((t_command *)pipeline->content)->argv, environ);
		restore_streams(&rdr);
	}
	else*/
	//	do_exec_pipeline(pipeline);



	pipe_nodes(pipeline);
	//print_pipeline(pipeline);
	pid = exec_command_list(pipeline);
	waitpid(pid, &status, 0);
	wait_pipeline(pipeline);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
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
