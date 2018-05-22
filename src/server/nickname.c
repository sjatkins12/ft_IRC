/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nickname.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 19:29:13 by satkins           #+#    #+#             */
/*   Updated: 2018/05/22 15:45:20 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"
#include "client_obj.h"

static int	check_nick(t_client client, char *nickname)
{
	size_t		len;
	t_client	iter_client;

	len = ft_strlen(nickname);
	if (len > MAX_NAME || len == 0)
	{
		send(client.client_id, "ERR_NICKTOOLONG", 15, 0);		
		return (EXIT_FAILURE);
	}
	len = 0;
	while (len < FD_SETSIZE)
	{
		iter_client = g_client_tab[len];
		if (iter_client.vtable &&
			ft_strequ(iter_client.vtable->get_nickname(iter_client), nickname))
		{
			send(client.client_id, "ERR_NICKCOLLISION", 17, 0);		
			return (EXIT_FAILURE);
		}
		len++;
	}
	return (EXIT_SUCCESS);
}

int	set_nick(t_client client, char *nickname)
{
	if (check_nick(client, nickname) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	client.vtable->set_nickname(client, nickname);
	if (send(client.client_id, "NICK", 4, 0) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int			nickname(int client_socket, char *msg)
{
	set_nick(g_client_tab[client_socket], ft_strchr(msg, ' ') + 1);
	return (EXIT_SUCCESS);
}