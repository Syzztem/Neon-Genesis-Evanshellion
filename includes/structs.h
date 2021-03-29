/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 14:48:30 by smaccary          #+#    #+#             */
/*   Updated: 2021/03/26 11:02:32 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include "libft.h"

typedef t_list * t_pipeline;
typedef t_list * t_ast;

typedef struct	s_ast_node
{
	char	**abstract_pipeline;
	char	*sep;
}				t_ast_node;

typedef struct	s_command
{
	char	*cmd;
	char	**argv;
	char	*sep;
	char	**tokens;
	char	**redirections;
	int		fd_output;
	int		fd_input;
	pid_t	pid;
}				t_command;

typedef struct	s_redirector
{
	char			**rtokens;
	int				in_fd;
	int				out_fd;
	int				stdin_dup;
	int				stdout_dup;
}				t_redirector;

#endif
