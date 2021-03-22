/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 15:36:45 by smaccary          #+#    #+#             */
/*   Updated: 2021/03/22 13:53:07 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "parser.h"
# include "global.h"
# include <sys/wait.h>

void	exec_command(t_command *command);
int		exec_command_list(t_list *commands);
int		exec_abstract_pipeline(char **tokens);
int     exec_command_line(char **tokens);
int		exec_builtin(char **av, char **envp);
int     exec_from_ast(t_ast ast);
int		is_builtin(char *command);
void    wait_command(t_command *cmd);

int     check_pipeline_run(char *condition, int last_return);

void    restore_streams(t_redirector *rdr);
void    redirect_command(t_command *cmd);
void    do_redirector(t_redirector *rdr, char **redirections);
void    dup2_check(int fd_src, int fd_dst);
void    close_checked(int fd);
int     pipe_nodes(t_list *commands);

void    close_cmd(t_command *cmd);
void    close_all_cmds(t_list *commands, t_command *avoid);

#endif
