/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:57:30 by smaccary          #+#    #+#             */
/*   Updated: 2021/04/02 12:31:24 by smaccary         ###   ########.fr       */
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
# include <limits.h>
# include "libft.h"
# include "structs.h"
# include "global.h"
# include "garbage_collector.h"

# define SHELL_NAME "minishell"
# define CMD_NOT_FOUND_MSG "command not found"

# define ESCAPE_CHAR 0x1b
# define ESCAPE "\x1b"
# define REDIR_REPLACE ESCAPE ">"
# define REDIR_APPEND ESCAPE ">>"
# define REDIR_HERE_DOC ESCAPE "<<"
# define REDIR_INPUT ESCAPE "<"
# define PIPE ESCAPE "|"
# define SEMICOLON  ";"
# define AND  "&&"
# define OR  "||"
# define PARENTHESIS_OPEN ESCAPE "("
# define PARENTHESIS_CLOSE ESCAPE ")"

# define OUTPUT_REPLACE_MASK 1
# define OUTPUT_APPEND_MASK  2
# define INPUT_REDIRECT_MASK 4

# ifndef DEBUG
#  define DEBUG 0
# endif

# define DEBUG_AST 0
# define DEBUG_SEP 0

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
size_t			pure_tokens_len(char **tokens, char **excluded_tokens);

int				is_redirect(char *token);
int				is_connective(char *token);

t_command		*get_next_command(char **tokens);
size_t			get_command_len(char **tokens);

char			**find_token_in_tokens(char **tokens, char **to_find);
char			**ref_in_tokens(char *ref, char **tokens);
char			**safe_find_token(char **tokens, char *find);
char			**get_last_token(char **tokens);

t_pipeline		parse_pipeline(char *pipeline);
t_ast			parse_ast(char **tokens);
char			**extract_redirects(char **tokens);

int				open_output(char **output_path_ptr);
int				redirects_to_fds(char **redirects, int *input, int *output);
int				check_path_ptr(char **path_ptr);

void			print_pipeline(t_pipeline lst);
void			print_command(t_command *command);
int				print_argv(char **argv);
void			print_ast(t_ast	ast);
void			psyntax_error(char *token);
void			pescaped_token(char *token, int fd);

char			*alloc_path_buf(char *cmd);
char			*do_find_exec(char *cmd);
void			print_exec_path(char *cmd);
void			iter_argv(char **argv, void (*func)(char *));

char			**separators(void);
char			**redirects(void);
char			**output_redirects(void);
char			**input_redirects(void);
char			**pipeline_separators(void);
char			**connectives(void);

int				check_pipeline(t_pipeline pipeline);
int				check_command(t_command *cmd);
int				check_ast(t_ast ast);
int				check_syntax(char **tokens);

#endif
