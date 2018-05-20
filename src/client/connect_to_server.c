/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_to_server.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 15:41:59 by satkins           #+#    #+#             */
/*   Updated: 2018/05/18 09:47:29 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"
#include "client_commands.h"
#include "termcap_utils.h"

int			command_loop(int server_socket);

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

int 		main (int argc, char **argv)
{
	int port;
	int	server_socket;

	if (argc != 3
		|| (!(port = ft_atoi(argv[1])) && argv[1][0] != '0')
		|| init_termcaps() == EXIT_FAILURE
		|| (server_socket = connect_to_server(port, argv[2])) == EXIT_FAILURE)
	{
		ft_printf("Usage: client port address\n");
		ft_printf("\tFor your host address 'dig +short `hostname`'\n");
		return (EXIT_FAILURE);
	}
	command_loop(server_socket);
	return (EXIT_SUCCESS);
}