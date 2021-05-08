/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:24:21 by smaccary          #+#    #+#             */
/*   Updated: 2021/05/08 23:45:57 by user42           ###   ########.fr       */
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

void
	fork_sigquit(int code)
{
	char *codestr;

	codestr = ft_itoa(code);
	ft_putstr_fd("Quit: ", 2);
	if (codestr)
		ft_putstr_fd(codestr, 2);
	write(2, "\n", 1);
	g_exit_status = 131;
	free(codestr);
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
	print_pipeline(pipeline);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, fork_sigquit);
	pid = exec_command_list(pipeline);
	waitpid(pid, &status, 0);
	wait_pipeline(pipeline);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else
		g_exit_status = 130;
	signal(SIGINT, (void *)interrupt_blank);
	signal(SIGQUIT, SIG_IGN);
	return (g_exit_status);
}

int
	check_pipeline_run(char *condition, int last_return)
{
	if (condition == NULL || !ft_strcmp(condition, SEMICOLON))
		return (1);
	if (!ft_strcmp(condition, AND) && last_return == 0)
		return (1);
	if (!ft_strcmp(condition, OR) && last_return != 0)
		return (1);
	return (0);
}
