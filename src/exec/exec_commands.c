/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:42:25 by smaccary          #+#    #+#             */
/*   Updated: 2021/03/22 14:01:11 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void
	exec_command(t_command *command)
{
	extern char		**environ;

	redirect_command(command);
	if (is_builtin(command->argv[0]) != -1)
		exit(exec_builtin(command->argv, environ));
	else
		execve(command->cmd, command->argv, environ);
	dprintf(2, "%s:%s:%d : %s : %s\n", SHELL_NAME, __FILE__, __LINE__,
		strerror(errno), command->cmd);
	exit(errno);
}

int
	exec_command_list(t_list *commands)
{
	t_list		*current;
	t_command	*cmd;

	current = commands;
	while (current)
	{
		cmd = current->content;
		cmd->pid = fork();
		if (cmd->pid == 0)
		{
			close_all_cmds(commands, cmd);
			exec_command(cmd);
		}
		current = current->next;
	}
	close_all_cmds(commands, NULL);
	return (0);
}

void
	wait_command(t_command *cmd)
{
	waitpid(cmd->pid, NULL, 0);
}
