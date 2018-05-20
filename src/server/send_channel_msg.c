/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_channel_msg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 20:35:11 by satkins           #+#    #+#             */
/*   Updated: 2018/05/19 19:33:10 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"
#include "channel.h"
#include "client_obj.h"
#include "channel_obj.h"
#include "msg.h"

t_channel	g_channel_tab[MAX_CHANNEL];

static int	find_channel_id(char *chan_name)
{
	int			i;
	t_channel	chan;

	i = 0;
	while (i < MAX_CHANNEL)
	{
		chan = g_channel_tab[i];
		if (!chan.vtab)
			return (-1);
		if (ft_strequ(chan.vtab->get_channel_name(chan), chan_name))
			return (i);
		i++;
	}
	return (-1);
}

int	join(int client_id, char *msg)
{
	int	channel_id;
	char		*chan_name;
	t_channel	chan;

	chan_name = ft_strchr(msg, ' ') + 1;
	if ((channel_id = find_channel_id(chan_name)) == -1)
	{
		chan = new_channel();
		if ((channel_id = chan.channel_id) == -1
			|| chan.vtab->set_channel_name(chan, chan_name) == EXIT_FAILURE)
		{
			send(client_id, "JOIN FAILED", 12, 0);
			return (EXIT_FAILURE);
		}
		g_channel_tab[channel_id] = chan;
		ft_printf("\033[1;33mNew Channel %s Created\n\033[0m", chan_name);
	}
	chan = g_channel_tab[channel_id];
	chan.vtab->add_member(chan, client_id);
	g_client_tab[client_id].vtable->set_channel(g_client_tab[client_id], channel_id);
	if (send(client_id, "JOIN SUCCESS", 12, 0) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

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

int	send_channel_msg(t_client client, char *msg)
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