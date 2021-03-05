/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 15:16:56 by smaccary          #+#    #+#             */
/*   Updated: 2021/03/05 15:41:18 by smaccary         ###   ########.fr       */
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
		cmd->pid = last_pid;
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

	pipe_nodes(commands);
	pid = exec_command_list(commands);
	print_cmd_lst(commands);
	waitpid(pid, NULL, 0);
	return (0);
}

int
	is_single_builtin(t_list	*lst)
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

	//print_argv(tokens);
	pure_tokens = get_pure_tokens(tokens);
	lst = parse_list(pure_tokens);
	//print_cmd_lst(lst);

	redirections = extract_redirects(tokens);
	redirects_to_fds(redirections, &fd_input, &fd_output);
	tmp_stdin = dup(0);
	tmp_stdout = dup(1);
	dup2(fd_input, 0);
	dup2(fd_output, 1);
	//print_argv(redirections);
	if (is_single_builtin(lst))
		exec_builtin(((t_command *)lst->content)->argv, environ);
	else
		exec_command_line(lst, redirections);
	dup2(tmp_stdout, 1);
	dup2(tmp_stdin, 0);
	return (0);
}
