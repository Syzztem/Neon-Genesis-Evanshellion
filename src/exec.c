/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 15:16:56 by smaccary          #+#    #+#             */
/*   Updated: 2021/03/15 23:36:19 by root             ###   ########.fr       */
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

void
	exec_command(t_command *command)
{
	extern char		**environ;
	t_redirector	redirector;

	dup2_check(command->fd_input, 0);
	dup2_check(command->fd_output, 1);
	if (is_builtin(command->argv[0]) != -1)
		exec_builtin(command->argv, environ);
	else
	{
	//	dprintf(2, "%s is not a builtin\n", command->cmd);
		execve(command->cmd, command->argv, environ);
	}
	dprintf(2, "%s : %s : %s\n", SHELL_NAME, strerror(errno), command->cmd);
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
	close(cmd->fd_input);
	close(cmd->fd_output);
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
	close_checked(int fd)
{
	if (fd != 0 && fd != 1)
		close (fd);
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
	do_redirector(t_redirector *rdr, char **tokens)
{
	rdr->rtokens = extract_redirects(tokens);
	redirects_to_fds(rdr->rtokens, &rdr->in_fd, &rdr->out_fd);
	rdr->stdin_dup = dup(0);
	rdr->stdout_dup = dup(1);
	dup2(rdr->in_fd, 0);
	dup2(rdr->out_fd, 1);
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
	char			**pure_tokens;
	t_redirector	redirector;
	extern	char	**environ;

	//do_redirector(&redirector, tokens);
	//pure_tokens = get_pure_tokens(tokens);
	pipeline = parse_pipeline(tokens);
	print_pipeline(pipeline);
	return (0);
	if (is_single_builtin(pipeline))
		exec_builtin(((t_command *)pipeline->content)->argv, environ);
	else
		exec_pipeline(pipeline);
	//restore_streams(&redirector);
//	printf("$? = %d\n", g_exit_status);
	return (0);
}
