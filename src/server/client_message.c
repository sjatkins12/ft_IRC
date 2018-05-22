/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_message.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 15:45:00 by satkins           #+#    #+#             */
/*   Updated: 2018/05/22 15:21:34 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"
#include "client_obj.h"
#include "client_funcs.h"

t_client		g_client_tab[FD_SETSIZE];

t_client_funcs	g_client_funcs[] = {
				{"NICK ", &nickname},
				{"PASS ", &pass},
				{"JOIN ", &join},
				{"COLOR ", &color},
				{"WHO\0", &who},
				{"CHAN ", &get_channels},
				{NULL, NULL}
};

/*
** Recv from a client socket. Check the client has had a valid handshake.
** Then check the message header and dispatch accordingly.
*/

static int		check_registered(int client_index, char *msg)
{
	if (!g_client_tab[client_index].pword_registered)
	{
		if (ft_strncmp(msg, "PASS ", 5))
		{
			send(client_index, "ERR_NOTREGISTERED", 17, 0);
			return (-1);
		}
	}
	else if (!((g_client_tab[client_index]).vtable->
		get_nickname(g_client_tab[client_index]))
		&& !ft_strnequ(msg, "NICK ", 5)
		&& !ft_strnequ(msg, "CHAN ", 5))
	{
		send(client_index, "ERR_NONICKSET", 13, 0);	
		return (-1);
	}
	return (EXIT_SUCCESS);
}

int				get_client_msg(int client_socket)
{
	t_client_funcs	tuple;
	char			buff[1024];
	int				i;

	ft_bzero(buff, sizeof(buff));
	recv(client_socket, buff, sizeof(buff), 0);
	if ((i = check_registered(client_socket, buff)) != EXIT_SUCCESS)
		return (i);
	i = 0;
	while (g_client_funcs[i].command)
	{
		tuple = g_client_funcs[i];
		if (ft_strnequ(tuple.command, buff, ft_strlen(tuple.command)))
		{
			g_client_funcs[i].func(client_socket, buff);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (send_channel_msg(g_client_tab[client_socket], buff));
}
