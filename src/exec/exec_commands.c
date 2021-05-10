/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:42:25 by smaccary          #+#    #+#             */
/*   Updated: 2021/05/10 23:52:32 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "tokenizer.h"
#include "vector.h"

int
	handle_empy_command(t_command *cmd)
{
	t_redirector	rdr;
	int				ret;

	if (!cmd->redirections)
		return (0);
	ret = do_redirector(&rdr, cmd->redirections);
	return (errno);
}

void
	ensure_cmd_sanity(t_command *command)
{
	//print_command(command);
	if (redirect_command(command) < 0)
		exit(errno);
	if (!command->cmd)
		exit(0);
}

void
	exec_command(t_command *command)
{
	extern char		**environ;
	int				ret;

	ret = 127;
	if (command->cmd == NULL)
		ret = handle_empy_command(command);
	else if (is_cmd_parenthesis(command))
		ret = exec_parenthesis(command);
	else
	{
		expand_command(command);
		ensure_cmd_sanity(command);
		if (is_builtin(command->argv[0]) != -1)
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
		if (current->next)
			link_commands(cmd, current->next->content);
		cmd->pid = fork();
		if (cmd->pid == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, SIG_DFL);
			if (current->next)
				close_checked(((t_command *)current->next->content)->fd_input);
			exec_command(cmd);
		}
		current = current->next;
		close_cmd(cmd);
	}
	return (cmd->pid);
}

void
	wait_command(t_command *cmd)
{
	waitpid(cmd->pid, NULL, 0);
}
