/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 15:16:56 by smaccary          #+#    #+#             */
/*   Updated: 2021/03/09 14:08:31 by smaccary         ###   ########.fr       */
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
	extern char **environ;

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
	exec_command_line(t_list *commands)
{
	pid_t	pid;
	int		status;

	pipe_nodes(commands);
	pid = exec_command_list(commands);
	print_cmd_lst(commands);
	waitpid(pid, &status, 0);
	wait_commands(commands);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	return (0);
}

int
	is_single_builtin(t_list *lst)
{
	t_command	*cmd;
	
	if (!lst || lst->next)
		return (0);
	cmd = lst->content;
	return (cmd && cmd->argv && is_builtin(cmd->argv[0]) != -1);
}

int
	exec_from_tokens(char **tokens)
{
	t_list			*lst;
	char			**pure_tokens;
	char			**redirections;
	extern	char	**environ;
	int				fd_input;
	int				fd_output;
	int				tmp_stdin;
	int				tmp_stdout;

	pure_tokens = get_pure_tokens(tokens);
	lst = parse_list(pure_tokens);
	redirections = extract_redirects(tokens);
	redirects_to_fds(redirections, &fd_input, &fd_output);
	tmp_stdin = dup(0);
	tmp_stdout = dup(1);
	dup2(fd_input, 0);
	dup2(fd_output, 1);
	if (is_single_builtin(lst))
		exec_builtin(((t_command *)lst->content)->argv, environ);
	else
		exec_command_line(lst);
	dup2_check(tmp_stdout, 1);
	dup2_check(tmp_stdin, 0);
//	printf("$? = %d\n", g_exit_status);
	return (0);
}
