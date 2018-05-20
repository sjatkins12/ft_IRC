/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_channel_msg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 20:35:11 by satkins           #+#    #+#             */
/*   Updated: 2018/05/19 23:54:42 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"
#include "channel.h"
#include "client_obj.h"
#include "channel_obj.h"
#include "msg.h"

t_channel	g_channel_tab[MAX_CHANNEL];



// int	who(int	client_id, char *msg)
// {
	
// }

static int	send_to_client(int client_id, char *msg, t_client client)
{
	char	buff[1024];
	t_msg_header	header;
	struct tm	*curr_time;
	time_t		time_type;

	ft_bzero(buff, sizeof(buff));
	time_type = time(NULL);
	curr_time = localtime(&time_type);
	ft_bzero(header.nickname, sizeof(header.nickname));
	ft_strcpy(header.nickname, client.vtable->get_nickname(client));
	header.color = split_color(client.vtable->get_color(client));
	header.hour = curr_time->tm_hour;
	header.min = curr_time->tm_min;
	ft_memcpy(buff, &(header), sizeof(t_msg_header));
	ft_strcpy(buff + sizeof(t_msg_header), msg);
	if (send(client_id, buff, sizeof(buff), 0) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int			send_channel_msg(t_client client, char *msg)
{
	int			channel_id;
	t_channel	chan;
	int			client_id;
	uint8_t		*client_members;

	if ((channel_id = client.vtable->get_channel(client)) == -1)
		return (EXIT_SUCCESS);
	chan = g_channel_tab[channel_id];
	client_members = chan.vtab->get_channel_members(chan);
	client_id = 0;
	while (client_id < FD_SETSIZE)
	{
		if (client_members[client_id] == 1)
			send_to_client(client_id, msg, client);
		client_id++;
	}
	return (EXIT_SUCCESS);
}
