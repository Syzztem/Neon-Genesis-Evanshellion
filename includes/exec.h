/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 15:36:45 by smaccary          #+#    #+#             */
/*   Updated: 2021/03/09 14:26:36 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "parser.h"

typedef struct  s_redirector
{	
    char			**rtokens;
	int				in_fd;
	int				out_fd;
	int				stdin_dup;
	int				stdout_dup;
}               t_redirector;


static int	g_exit_status = 0;

void	exec_command(t_command *command);
int		exec_list(t_list *commands, char **redirections);
int		exec_from_tokens(char **tokens);
int		exec_builtin(char **av, char **envp);
int		is_builtin(char *command);


#endif
