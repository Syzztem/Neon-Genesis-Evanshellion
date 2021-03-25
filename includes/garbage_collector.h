/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 14:27:44 by smaccary          #+#    #+#             */
/*   Updated: 2021/03/25 19:38:47 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

# include "structs.h"
# include <stdlib.h>
# include "libft.h"

void    free_to_null(void **ptr);
void    free_tokens(char **tokens);
void    free_cmd(t_command *cmd);
void    free_ast_node(t_ast_node *node);
void    free_ast(t_ast ast);
void    free_pipeline(t_pipeline *pipeline);
#endif
