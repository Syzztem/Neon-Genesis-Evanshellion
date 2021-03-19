/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 15:16:56 by smaccary          #+#    #+#             */
/*   Updated: 2021/03/19 14:41:20 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "exec.h"

void
	close_checked(int fd)
{
	if (fd != 0 && fd != 1)
		close (fd);
}

static void
	dup2_check(int fd_src, int fd_dst)
{
	if (fd_src != fd_dst && fd_dst >= 0)
	{
		dup2(fd_src, fd_dst);
		close(fd_src);
	}
}

void
	do_redirector(t_redirector *rdr, char **redirections)
{
	rdr->rtokens = redirections;
	redirects_to_fds(rdr->rtokens, &rdr->in_fd, &rdr->out_fd);
	rdr->stdin_dup = dup(0);
	rdr->stdout_dup = dup(1);
	dup2(rdr->in_fd, 0);
	dup2(rdr->out_fd, 1);
}

void
	redirect_command(t_command *cmd)
{
	t_redirector	rdr;

	do_redirector(&rdr, cmd->redirections);
}

void
	exec_command(t_command *command)
{
	extern char		**environ;

	dup2_check(command->fd_input, 0);
	dup2_check(command->fd_output, 1);
	//redirect_command(command);
	if (is_builtin(command->argv[0]) != -1)
		exit(exec_builtin(command->argv, environ));
	else
	{
	//	dprintf(2, "%s is not a builtin\n", command->cmd);
		execve(command->cmd, command->argv, environ);
	}
	dprintf(2, "%s:%s:%d : %s : %s\n", SHELL_NAME, __FILE__, __LINE__ , strerror(errno), command->cmd);
	exit(errno);
	print_command(command);
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

void
	close_cmd(t_command *cmd)
{
	if (DEBUG)
	{
		puts("CLOSING:");
		print_command(cmd);
	}
	close_checked(cmd->fd_input);
	close_checked(cmd->fd_output);
	if (DEBUG)
		puts("CLOSED");
}

void close_all_cmds(t_list *commands, t_command *avoid)
{
	t_list	*current;

	current = commands;
	while (current)
	{
		if (avoid != current->content)
			close_cmd(current->content);
		current = current->next;
	}
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

void
	wait_commands(t_list *lst)
{
	ft_lstiter(lst, (void *)wait_command);
}

int
	exec_pipeline(t_list *commands)
{
	pid_t	pid;
	int		status;

	pipe_nodes(commands);
	pid = exec_command_list(commands);
	print_pipeline(commands);
	waitpid(pid, &status, 0);
	wait_commands(commands);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	return (0);
}

int
	is_single_builtin(t_pipeline lst)
{
	t_command	*cmd;
	
	if (!lst || lst->next)
		return (0);
	cmd = lst->content;
	return (cmd && cmd->argv && is_builtin(cmd->argv[0]) != -1);
}

void
	restore_streams(t_redirector *rdr)
{
	dup2_check(rdr->stdout_dup, 1);
	dup2_check(rdr->stdin_dup, 0);
}

int
	exec_abstract_pipeline(char **tokens)
{
	t_pipeline		pipeline;
	extern	char	**environ;
	t_redirector	rdr;

	pipeline = parse_pipeline(tokens);
	print_pipeline(pipeline);
	if (is_single_builtin(pipeline))
	{
		do_redirector(&rdr, ((t_command *)pipeline->content)->redirections);
		exec_builtin(((t_command *)pipeline->content)->argv, environ);
		restore_streams(&rdr);
	}
	else
		exec_pipeline(pipeline);
//	printf("$? = %d\n", g_exit_status);
	return (0);
}
