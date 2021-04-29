/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 15:36:45 by smaccary          #+#    #+#             */
/*   Updated: 2021/04/29 20:58:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "parser.h"
# include <sys/wait.h>
# include "vector.h"


int		here_doc(char *end_mark);
int		exec_single_builtin(t_command *cmd);
int		minishell(void);
int		exec_pipeline(t_pipeline pipeline);
void	exec_command(t_command *command);
int		exec_command_list(t_list *commands);
int		exec_abstract_pipeline(char *tokens);
int		exec_command_line(char **tokens);
int		exec_line(char **commands);
int		exec_builtin(char **av, char **envp);
int		exec_from_ast(t_ast ast);
int		is_builtin(char *command);
void	wait_command(t_command *cmd);

int		check_pipeline_run(char *condition, int last_return);

void	restore_streams(t_redirector *rdr);
void	redirect_command(t_command *cmd);
void	do_redirector(t_redirector *rdr, char **redirections);
void	dup2_check(int fd_src, int fd_dst);
void	close_checked(int fd);
int		pipe_nodes(t_list *commands);

void	close_cmd(t_command *cmd);
void	close_all_cmds(t_list *commands, t_command *avoid);
void	switch_stdout(void);
void	pcmd_not_found(t_command *cmd);
int	    is_shell_interactive(void);

int		open_redir(char	**redir);
int     open_input(char	**input_path_ptr);
char	**split_line(char *line);
char	**split_quotes(char	*str);
void	expand_command(t_command *command);
void	expand_redir(char ***redir_ptr, t_vector *argv_vect);
#endif
