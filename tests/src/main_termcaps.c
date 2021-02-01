/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_termcaps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 17:08:44 by lothieve          #+#    #+#             */
/*   Updated: 2021/02/01 10:35:24 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

int main()
{
	char *line;
	tgetent(NULL, getenv("TERM"));
	t_term term;
	t_term backup;
	tcgetattr(0, &term);
	tcgetattr(0, &backup);
	term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, 0, &term);
	setbuf(stdout, NULL);
	cap("ks");
	ft_putstr_fd("s e x y p r o m p t >> ", 0);
	while (get_term_line(&line))
	{
		puts(line);
		free(line);
	}
	tcsetattr(0, 0, &backup);
	system("leaks a.out | awk '/----/{y=2;next}y' | lolcat");
}
