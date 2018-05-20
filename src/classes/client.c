/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 13:48:55 by satkins           #+#    #+#             */
/*   Updated: 2018/05/19 19:54:34 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"
#include "libft.h"
/*
** This is a client class used to recreate some functionality of an oop lang
*/

char		g_m_nickname_tab[FD_SETSIZE][MAX_NAME + 1];
int			g_m_channel_tab[FD_SETSIZE];
int			g_m_color_tab[FD_SETSIZE];

int			get_channel(t_client self);
void		set_channel(t_client self, int channel_id);
char		*get_nickname(t_client self);
void		set_nickname(t_client self, char *name);
void		set_color(t_client self, int color);
int			get_color(t_client self);

const t_client_vtable	vtab = {
			&set_nickname,
			&get_nickname,
			&set_channel,
			&get_channel,
			&set_color,
			&get_color
};

t_client	new_client(int id)
{
	t_client	new_client;

	new_client.client_id = id;
	new_client.vtable = &vtab;
	new_client.pword_registered = 0;
	ft_bzero(g_m_nickname_tab[id], MAX_NAME + 1);
	g_m_channel_tab[id] = -1;
	g_m_color_tab[id] = DEFAULT_COLOR;
	return (new_client);
}

void	set_nickname(t_client self, char *name)
{
	ft_bzero(g_m_nickname_tab[self.client_id], MAX_NAME + 1);
	ft_strncpy(g_m_nickname_tab[self.client_id], name, MAX_NAME);
}

char	*get_nickname(t_client self)
{
	if (g_m_nickname_tab[self.client_id][0] == '\0')
		return (NULL);
	return (g_m_nickname_tab[self.client_id]);
}

void	set_channel(t_client self, int channel_id)
{
	g_m_channel_tab[self.client_id] = channel_id;
}

int		get_channel(t_client self)
{
	return (g_m_channel_tab[self.client_id]);
}

void	set_color(t_client self, int color)
{
	if (color <= 0xFFFFFF && color > 0)
		g_m_color_tab[self.client_id] = color;
}

int		get_color(t_client self)
{
	return (g_m_color_tab[self.client_id]);
}
