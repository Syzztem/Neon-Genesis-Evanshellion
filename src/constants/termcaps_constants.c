/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_constants.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 15:30:50 by smaccary          #+#    #+#             */
/*   Updated: 2021/04/30 16:00:26 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

/*
** That makes no sense at all but
** #4 is the shift + left key
** %i is the shift + right key
** Now I can die in peace for finding them
** And they both return the same value :)
*/

char
	**g_capstr(void)
{
	static char *array[] = {
	"kl",
	"kr",
	"#4",
	"%i",
	"#4",
	"#4",
	"kh",
	"@7",
	"ku"
	};

	return (array);
}

t_cap
	*g_caps(void)
{
	static t_cap	array[] = {
		move_left,
		move_right,
		prev_word,
		next_word,
		move_down,
		move_up,
		go_home,
		go_end,
		retreive_hist
	};

	return (array);
}
