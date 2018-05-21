/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_to_server.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 15:41:59 by satkins           #+#    #+#             */
/*   Updated: 2018/05/20 13:35:07 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"
#include "client_commands.h"
#include "termcap_utils.h"

static int	register_connection(int server_socket)
{
	if (prompt_pass(server_socket) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (send_nick(server_socket, getenv("USER")) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int			connect_to_server(int port, char *host)
{
	int	server_socket;

	if ((server_socket = create_client_sock(port, host)) == -1)
	{
		ft_printf("client socket failed\n");
		return (EXIT_FAILURE);
	}
	if (register_connection(server_socket) == EXIT_FAILURE)
	{
		ft_printf("register failed\n");
		return (EXIT_FAILURE);
	}
	return (server_socket);
}
