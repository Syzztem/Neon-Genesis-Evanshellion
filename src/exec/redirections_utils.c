/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:09:23 by smaccary          #+#    #+#             */
/*   Updated: 2021/03/22 14:47:44 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void
	close_checked(int fd)
{
	if (fd != 0 && fd != 1)
		close(fd);
}

void
	dup2_check(int fd_src, int fd_dst)
{
	if (fd_src != fd_dst && fd_dst >= 0)
	{
		dup2(fd_src, fd_dst);
		close(fd_src);
	}
}
