/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:42:25 by smaccary          #+#    #+#             */
/*   Updated: 2021/05/04 13:35:26 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "tokenizer.h"
#include "vector.h"

int
	exec_parenthesis(t_command *cmd)
{
	extern char	**environ;

	redirect_command(cmd);
	return (builtin_parenthesis(cmd->argv, environ));
}

int
	is_cmd_parenthesis(t_command *cmd)
{
	return (!ft_strcmp(PARENTHESIS_OPEN, cmd->cmd));
}

void
	exec_command(t_command *command)
{
	extern char		**environ;
	int				ret;

	ret = 127;
	if (is_cmd_parenthesis(command))
		ret = exec_parenthesis(command);
	else
	{
		expand_command(command);
		print_command(command);
		redirect_command(command);
		if (!command->cmd)
			exit(0);
		else if (is_builtin(command->argv[0]) != -1)
			ret = exec_builtin(command->argv, environ);
		else
		{
			execve(command->cmd, command->argv, environ);
			pcmd_not_found(command);
		}
	}
	free_cmd(command);
	free_env();
	exit(ret);
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
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, SIG_DFL);
			close_all_cmds(commands, cmd);
			exec_command(cmd);
		}
		current = current->next;
	}
	close_all_cmds(commands, NULL);
	return (cmd->pid);
}

void
	wait_command(t_command *cmd)
{
	waitpid(cmd->pid, NULL, 0);
}
