/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 22:02:33 by root              #+#    #+#             */
/*   Updated: 2021/04/22 17:27:55 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "exec.h"

int
    builtin_parenthesis(char **av, char **envp)
{
    char    **last;
    size_t  len;
    char    **sub_argv;
    int     ret;

    (void)envp;
    last = get_last_token(av);
    //printf("parenthesis: %s ");
    //print_argv(av);
    //printf("\n");
    if (strcmp(*last, PARENTHESIS_CLOSE))
    {
        ft_putstr_fd(SHELL_NAME ": syntax error: missing `)'\n", 2);
        return (1);
    }
    len = last - av;
    sub_argv = dup_n_tab(av + 1, len - 1);
    ret = exec_command_line(sub_argv);
    free_tokens(sub_argv);
    return (ret);
}
