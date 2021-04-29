/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 14:27:44 by smaccary          #+#    #+#             */
/*   Updated: 2021/04/29 23:07:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

# include "structs.h"
# include <stdlib.h>
# include "libft.h"
# include "termcaps.h"

void	free_line(t_line *line);
void	free_to_null(void **ptr);
void	free_tokens(char **tokens);
void	free_cmd(t_command *cmd);
void	free_ast_node(t_ast_node *node);
void	free_ast(t_ast ast);
void	free_pipeline(t_pipeline *pipeline);

#endif
