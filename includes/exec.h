/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 15:36:45 by smaccary          #+#    #+#             */
/*   Updated: 2021/03/20 21:04:20 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "parser.h"

# include <sys/wait.h>

void	exec_command(t_command *command);
int		exec_list(t_list *commands, char **redirections);
int		exec_abstract_pipeline(char **tokens);
int     exec_command_line(char **tokens);
int		exec_builtin(char **av, char **envp);
int		is_builtin(char *command);


#endif
