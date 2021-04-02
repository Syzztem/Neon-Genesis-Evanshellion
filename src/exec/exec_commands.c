/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:42:25 by smaccary          #+#    #+#             */
/*   Updated: 2021/04/02 12:55:12 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/*
void
	exec_parenthesis(t_command *cmd)
{
	int		pipes[2];
	pid_t	pid;
	int		status;

	pipe(pipes);
	write(pipes[1], cmd->cmd + 2, ft_strlen(cmd + 2) - 1);
	close(pipes[1]);
	pid = fork();
	if (pid == 0)
		exit(minishell());
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	return (g_exit_status);
	
}
*/

void
	exec_parenthesis(t_command *cmd)
{
	int		pipes[2];

	pipe(pipes);
	write(pipes[1], cmd->cmd + 2, ft_strlen(cmd->cmd + 2) - 1);
	close(pipes[1]);
	exit(minishell());
}

int
	is_cmd_parenthesis(t_command *cmd)
{
	return (!ft_strncmp(PARENTHESIS_OPEN, cmd->cmd, 2));
}

void
	exec_command(t_command *command)
{
	extern char		**environ;

	redirect_command(command);
	if (is_cmd_parenthesis(command))
		exec_parenthesis(command);
	else if (is_builtin(command->argv[0]) != -1)
		exit(exec_builtin(command->argv, environ));
	else
		execve(command->cmd, command->argv, environ);
	pcmd_not_found(command);
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
