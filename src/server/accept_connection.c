/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accept_connection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 12:14:30 by satkins           #+#    #+#             */
/*   Updated: 2018/05/20 11:24:29 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"
#include "client_obj.h"

t_client	g_client_tab[FD_SETSIZE];

/*
** Accept new client connections. Also create new client object
*/

int	accept_new_client(int master_fd, fd_set *cpy)
{
	t_sockaddr_in	client_addr;
	const size_t	addrlen = sizeof(t_sockaddr_in);
	int				newsock;

	if ((newsock = accept(master_fd, (t_sockaddr *)&client_addr,
		(socklen_t *)&addrlen)) == -1)
		return (EXIT_FAILURE);
	FD_SET(newsock, cpy);
	ft_bzero(&(g_client_tab[newsock]), sizeof(t_client));
	g_client_tab[newsock] = new_client(newsock);
	return (EXIT_SUCCESS);
}
