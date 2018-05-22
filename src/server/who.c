/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 23:55:15 by satkins           #+#    #+#             */
/*   Updated: 2018/05/22 15:07:14 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"
#include "channel.h"
#include "client_obj.h"
#include "channel_obj.h"

static int	get_chan(t_client client, t_channel *chan)
{
	int		channel_id;

	if ((channel_id = client.vtable->get_channel(client)) == -1)
		return (EXIT_FAILURE);
	*chan = g_channel_tab[channel_id];
	return (EXIT_SUCCESS);
}

static int	add_to_list(int client_id, char *buff)
{
	t_client	client;

	client = g_client_tab[client_id];
	ft_strcat(buff, client.vtable->get_nickname(client));
	ft_strcat(buff, "\n");
	return (EXIT_SUCCESS);
}

static int	send_list(int client_sock, uint8_t *members, t_channel chan)
{
	char	buff[1024];
	int		i;

	ft_bzero(buff, sizeof(buff));
	ft_strcpy(buff, "WHO Members of ");
	ft_strcat(buff, chan.vtab->get_channel_name(chan));
	ft_strcat(buff, ":\n");
	i = 0;
	while (i < FD_SETSIZE)
	{
		if (members[i])
			add_to_list(i, buff);
		i++;
	}
	if (send(client_sock, buff, sizeof(buff), 0) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	send_failure(int client_sock)
{
	if (send(client_sock, "FAILED", 6, 0) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	who(int	client_id, __attribute__((unused))char *msg)
{
	t_channel	chan;
	t_client	client;
	uint8_t		*chan_members;

	client = g_client_tab[client_id];
	if (get_chan(client, &chan) == EXIT_FAILURE)
	{
		if (send_failure(client_id) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	chan_members = chan.vtab->get_channel_members(chan);
	if (send_list(client_id, chan_members, chan) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
