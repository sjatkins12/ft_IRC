/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_set_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 17:36:59 by satkins           #+#    #+#             */
/*   Updated: 2018/05/17 14:08:04 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fd_set_utils.h"

t_fd_sets	set_constructor()
{
	t_fd_sets	new_sets;

	if (!(new_sets.cpy = malloc(sizeof(fd_set)))
		|| !(new_sets.fds = malloc(sizeof(fd_set))))
		return ((t_fd_sets){NULL, NULL});
	return (new_sets);
}

void	set_destructor(t_fd_sets sets)
{
	free(sets.fds);
	free(sets.cpy);
}

void	create_sets(t_fd_sets sets, int fd)
{
	FD_ZERO(sets.fds);
	FD_ZERO(sets.cpy);
	FD_SET(fd, sets.cpy);
	FD_SET(fd, sets.fds);
}

void	reset_fd_set(t_fd_sets sets)
{
	FD_ZERO(sets.fds);
	FD_COPY(sets.cpy, sets.fds);
}

int		check_closed_socket(int fd, fd_set *cpy)
{
	int		bytes_read;
	char	buff[1024];
	
	if ((bytes_read = recv(fd, buff, sizeof(buff),
		MSG_PEEK | MSG_DONTWAIT)) == 0)
	{
		close(fd);
		FD_CLR(fd, cpy);
	}
	else if (bytes_read == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
