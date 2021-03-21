/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:57:30 by smaccary          #+#    #+#             */
/*   Updated: 2021/03/21 14:23:55 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <string.h>
# include <errno.h>
# include "libft.h"
# include "global.h"

# define SHELL_NAME "minishell"
# define CMD_NOT_FOUND_MSG "command not found"

# define REDIR_REPLACE ">"
# define REDIR_APPEND ">>"
# define REDIR_INPUT "<"
# define PIPE "|"
# define SEMICOLON ";"
# define AND "&&"
# define OR "||"


# define SEPARATORS (char *[]){PIPE, SEMICOLON, NULL}
# define REDIRECTS (char *[]){REDIR_REPLACE, REDIR_APPEND, REDIR_INPUT, NULL}
# define OUTPUT_REDIRECTS (char *[]){REDIR_REPLACE, REDIR_APPEND, NULL}
# define INPUT_REDIRECTS (char *[]){REDIR_INPUT, NULL}

# define PIPELINE_SEPARATORS (char *[]){SEMICOLON, AND, OR, NULL}

# define OUTPUT_REPLACE_MASK 0b001
# define OUTPUT_APPEND_MASK  0b010
# define INPUT_REDIRECT_MASK 0b100

# ifndef DEBUG
#  define DEBUG 0
# endif

# define DEBUG_AST 1


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

typedef struct  s_redirector
{	
    char			**rtokens;
	int				in_fd;
	int				out_fd;
	int				stdin_dup;
	int				stdout_dup;
}               t_redirector;

size_t			get_pipeline_len(char **tokens);
size_t			tab_size(char **table);
t_command		*new_command(char *cmd, char **argv, char *sep);
t_command		*command_from_tokens(char **argv, char *sep);
char			**find_token(char *token, char **tokens_table);
char			**find_last_token(char *token, char **tokens_table);
char			**tab_find_last_token(char **tokens, char **tokens_table);
char			**get_pure_tokens(char **tokens);
int				is_sep(char *token);
char			**find_sep(char **tokens);
char			**find_pipe(char **tokens);
char			**dup_n_tab(char **table, size_t n);
size_t			get_command_len(char **tokens);

char			**find_token_in_tokens(char **tokens, char **to_find);

t_pipeline		parse_pipeline(char **tokens);
t_ast			parse_ast(char **tokens);
char			**extract_redirects(char **tokens);

int				redirects_to_fds(char **redirects, int *fd_input, int *fd_output);
	
void			print_pipeline(t_pipeline lst);
void			print_command(t_command *command);
int				print_argv(char **argv);
void			print_ast(t_ast	ast);

char			*alloc_path_buf(char *cmd);
char			*do_find_exec(char *cmd);
void			print_exec_path(char *cmd);
void			iter_argv(char **argv, void (*func)(char *));
#endif
