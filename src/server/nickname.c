/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nickname.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 19:29:13 by satkins           #+#    #+#             */
/*   Updated: 2018/05/20 11:39:57 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"
#include "client_obj.h"

static int	check_nick(char *nickname)
{
	size_t	len;

	len = ft_strlen(nickname);
	if (len > MAX_NAME || len == 0)
		return (EXIT_FAILURE);
	/* TODO: Add nickname collision */
	return (EXIT_SUCCESS);
}

int	set_nick(t_client client, char *nickname)
{
	if (check_nick(nickname) == EXIT_FAILURE)
	{
		send(client.client_id, "ERR_NICKTOOLONG", 15, 0);
		return (EXIT_FAILURE);
	}
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