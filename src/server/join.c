/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 23:44:02 by satkins           #+#    #+#             */
/*   Updated: 2018/05/20 18:58:40 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"
#include "channel.h"
#include "client_obj.h"
#include "channel_obj.h"
#include "msg.h"

static int		send_channel_join(t_channel chan, t_client client)
{
	uint8_t			*members;
	int				i;
	t_msg_header	header;
	char			buff[1024];

	ft_bzero(&header, sizeof(t_msg_header));
	ft_bzero(buff, sizeof(buff));
	ft_strcpy(header.msg_type, "SERVMSG");
	ft_memcpy(buff, &header, sizeof(t_msg_header));
	ft_strcpy(&(buff[sizeof(t_msg_header)]), client.vtable->get_nickname(client));
	ft_strcat(&(buff[sizeof(t_msg_header)]), " has joined the channel");
	members = chan.vtab->get_channel_members(chan);
	i = 0;
	while (i < FD_SETSIZE)
	{
		if (i != client.client_id && members[i] == 1)
			send(i, buff, sizeof(buff), 0);
		i++;
	}
	return (EXIT_SUCCESS);
}

static int		find_channel_id(char *chan_name)
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

/*
** Remove client from old channel (if one exists). Add client to new channel
*/

static int		switch_channels(t_client client, int new_channel_id)
{
	int			old_channel_id;
	t_channel	old_channel;
	t_channel	new_channel;

	new_channel = g_channel_tab[new_channel_id];
	old_channel_id = client.vtable->get_channel(client);
	if (old_channel_id != -1)
	{
		old_channel = g_channel_tab[old_channel_id];
		old_channel.vtab->remove_member(old_channel, client.client_id);
	}
	new_channel.vtab->add_member(new_channel, client.client_id);
 	client.vtable->set_channel(client, new_channel_id);
	return (EXIT_SUCCESS);
}

static int		create_new_channel(int client_id, char *chan_name, int *chan_id)
{
	t_channel	chan;
	int			channel_id;

	if (!chan_name)
		return (-1);
	chan = new_channel();
	if ((channel_id = chan.channel_id) == -1
		|| chan.vtab->set_channel_name(chan, chan_name) == EXIT_FAILURE)
	{
		if (send(client_id, "FAILED", 12, 0) == 1) /* TODO: Change to error code */
			return (EXIT_FAILURE);
		return (-1);
	}
	g_channel_tab[channel_id] = chan;
	ft_printf("\033[1;33mNew Channel %s Created\n\033[0m", chan_name);
	*chan_id = channel_id;
	return (EXIT_SUCCESS);
}

/*
** Check if channel exists. If it doesn't create a new channel. Then switch a
** client to the specified channel.
*/

int				join(int client_id, char *msg)
{
	int			ret;
	int			channel_id;
	char		*chan_name;

	chan_name = ft_strchr(msg, ' ') + 1;
	if ((channel_id = find_channel_id(chan_name)) == -1)
	{
		if ((ret = create_new_channel(client_id, chan_name, &channel_id)) !=
			EXIT_SUCCESS)
			return (ret == EXIT_FAILURE ? EXIT_FAILURE : EXIT_SUCCESS);
	}
	switch_channels(g_client_tab[client_id], channel_id);
	if (send(client_id, "JOIN", 4, 0) == -1)
		return (EXIT_FAILURE);
	send_channel_join(g_channel_tab[channel_id], g_client_tab[client_id]);
	return (EXIT_SUCCESS);
}
