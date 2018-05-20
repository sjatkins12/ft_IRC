/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 17:42:28 by satkins           #+#    #+#             */
/*   Updated: 2018/05/16 21:31:05 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "channel.h"

uint8_t		g_channel_members[MAX_CHANNEL][FD_SETSIZE];
int			g_channel_num_members[MAX_CHANNEL];
char		*g_channel_name[MAX_CHANNEL];

int			get_num_members(t_channel self);
uint8_t		*get_channel_members(t_channel self);
void		remove_member(t_channel self, int client_id);
void		add_member(t_channel self, int client_id);
int			set_channel_name(t_channel self, char *name);
char		*get_channel_name(t_channel self);

const t_channel_vtable	chan_vtab = {
	&add_member,
	&remove_member,
	&get_channel_members,
	&get_num_members,
	&set_channel_name,
	&get_channel_name
};

t_channel	new_channel(void)
{
	static int	id = 0;
	t_channel	new_channel;

	if (id == MAX_CHANNEL)
		return ((t_channel){-1, NULL});
	new_channel.channel_id = id;
	ft_bzero(g_channel_members[id], sizeof(g_channel_members[id]));
	g_channel_num_members[id] = 0;
	new_channel.vtab = &chan_vtab;
	g_channel_name[id] = NULL;
	id++;
	return (new_channel);
}

void		add_member(t_channel self, int client_id)
{
	if (!g_channel_members[self.channel_id][client_id])
		g_channel_num_members[self.channel_id]++;
	g_channel_members[self.channel_id][client_id] = 1;
}

void		remove_member(t_channel self, int client_id)
{
	if (g_channel_members[self.channel_id][client_id])
		g_channel_num_members[self.channel_id]--;
	g_channel_members[self.channel_id][client_id] = 0;
}

uint8_t		*get_channel_members(t_channel self)
{
	return (g_channel_members[self.channel_id]);
}

int			get_num_members(t_channel self)
{
	return (g_channel_num_members[self.channel_id]);
}

int			set_channel_name(t_channel self, char *name)
{
	char	*chan_name;

	if (!(chan_name = ft_strdup(name)))
		return (EXIT_FAILURE);
	g_channel_name[self.channel_id] = chan_name;
	return (EXIT_SUCCESS);
}

char		*get_channel_name(t_channel self)
{
	return (g_channel_name[self.channel_id]);
}
