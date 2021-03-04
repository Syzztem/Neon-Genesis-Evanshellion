/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 15:16:56 by smaccary          #+#    #+#             */
/*   Updated: 2021/03/04 17:08:50 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "exec.h"

static void
	dup2_check(int fd_src, int fd_dst)
{
	if (fd_src != fd_dst && fd_dst >= 0)
	{
		dup2(fd_src, fd_dst);
		close(fd_src);
	}
}

int
	exec_command(t_command *command)
{
	extern char **environ;
	pid_t	    pid;
	
	pid = fork();
	if (pid == 0)
	{
		dup2_check(command->fd_input, 0);
		dup2_check(command->fd_output, 1);
		if (is_builtin(command->argv[0]) != -1)
			exec_builtin(command->argv, environ);
		else
		{
		//	dprintf(2, "%s is not a builtin\n", command->cmd);
			pid = execve(command->cmd, command->argv, environ);
		}
		dprintf(2, "%s : %s : %s\n", SHELL_NAME, strerror(errno), command->cmd);
		exit(errno);
	}
	print_command(command);
	return (pid);
}

int
	link_commands(t_command *src, t_command *dst)
{
	int	pipes[2];
	int	ret;

	ret = pipe(pipes);
	src->fd_output = pipes[1];
	dst->fd_input = pipes[0];
	return (ret);
}

int
	pipe_nodes(t_list *commands)
{
	t_list	*current;
	int		ret;

	current = commands;
	ret = 0;
	while (current && current->next && ret == 0)
	{
		ret = link_commands(current->content, current->next->content);
		current = current->next;
	}
	return (ret);
}

pid_t
	exec_command_list(t_list *commands)
{	
	pid_t		last_pid;
	t_list		*current;
	t_command	*cmd;

	current = commands;
	while (current)
	{
		cmd = current->content;
		last_pid = exec_command(cmd);
		close(cmd->fd_input);
		close(cmd->fd_output);
		current = current->next;
	}
	
	return (last_pid);
}

void
	close_checked(int fd)
{
	if (fd != 0 && fd != 1)
		close (fd);
}

int
	exec_command_line(t_list *commands, char **redirections)
{
	pid_t	pid;
	int		fd_input;
	int		fd_output;

	fd_input = -2;
	fd_output = -2;
	pid = fork();
	if (pid == 0)
	{	
		redirects_to_fds(redirections, &fd_input, &fd_output);
		pipe_nodes(commands);
		print_cmd_lst(commands);
		dup2_check(fd_output, 1);
		dup2_check(fd_input, 0);
		pid = exec_command_list(commands);
		close(fd_output);
		close(fd_input);
		waitpid(pid, NULL, 0);
		exit(0);
	}
	waitpid(pid, NULL, 0);
	return (0);
}

int
	exec_from_tokens(char **tokens)
{
	t_list	*lst;
	char	**pure_tokens;
	char	**redirections;

	//print_argv(tokens);
	pure_tokens = get_pure_tokens(tokens);
	lst = parse_list(pure_tokens);
	//print_cmd_lst(lst);

	redirections = extract_redirects(tokens);
	//print_argv(redirections);
	exec_command_line(lst, redirections);
	return (0);
}
