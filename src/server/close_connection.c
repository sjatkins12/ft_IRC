/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_connection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:00:41 by satkins           #+#    #+#             */
/*   Updated: 2018/05/20 11:28:39 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"
#include "client_obj.h"
#include "channel_obj.h"

/*
** Remove client any channel table it may be in.
*/

int	close_client(int client_socket)
{
	int			channel_id;
	t_client	client;
	t_channel	chan;

	client = g_client_tab[client_socket];
	if ((channel_id = client.vtable->get_channel(client)) != -1)
	{
		chan = g_channel_tab[channel_id];
		chan.vtab->remove_member(chan, client_socket);
	}
	ft_bzero(&(g_client_tab[client_socket]), sizeof(t_client));
	return (EXIT_SUCCESS);
}
	