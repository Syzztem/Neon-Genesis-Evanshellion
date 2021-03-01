/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 15:36:45 by smaccary          #+#    #+#             */
/*   Updated: 2021/02/26 10:37:34 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "parser.h"

int     exec_command(t_command *command);
int     exec_list(t_list *commands, char **redirections);
int	    exec_from_tokens(char **tokens);
void    exec_builtin(char **av, char **envp);
int		is_builtin(char *command);


#endif
