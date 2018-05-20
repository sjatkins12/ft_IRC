/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 13:48:17 by satkins           #+#    #+#             */
/*   Updated: 2018/05/17 15:47:08 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"
#include "ft_select.h"

static int	new_sets(t_fd_sets *sets)
{
	if (!sets)
		return (EXIT_FAILURE);
	*sets = set_constructor();
	if (!sets->cpy || !sets->fds)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	client_action(int client_socket, fd_set *cpy)
{
	if (check_closed_socket(client_socket, cpy) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	else if (FD_ISSET(client_socket, cpy))
		return (get_client_msg(client_socket));
	else
		return (close_client(client_socket));
}

static int	iter_fds(const t_select_dispatch dis, t_fd_sets sets)
{
	int		fd;

	fd = 0;
	while (fd < FD_SETSIZE)
	{
		if (FD_ISSET(fd, sets.fds))
		{
			if (fd == dis.new_connection_socket)
			{
				if (dis.accept_connection(fd, sets.cpy) == EXIT_FAILURE)
					return (EXIT_FAILURE);
			}
			else if (dis.client_action(fd, sets.cpy) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		fd++;
	}
	return (EXIT_SUCCESS);
}

int		select_loop(int connection_sock)
{
	t_fd_sets	sets;
	const t_select_dispatch	dis = {
		connection_sock,
		&accept_new_client,
		&client_action
	};

	if (new_sets(&sets) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	create_sets(sets, connection_sock);
	while (1)
	{
		if (select(FD_SETSIZE, sets.fds, NULL, NULL, NULL) == -1
			|| iter_fds(dis, sets) == EXIT_FAILURE)
		{
			set_destructor(sets);
			return (EXIT_FAILURE);
		}
		reset_fd_set(sets);
	}
	set_destructor(sets);
	return (EXIT_SUCCESS);
}
