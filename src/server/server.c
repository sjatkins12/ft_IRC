/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 14:04:11 by satkins           #+#    #+#             */
/*   Updated: 2018/05/16 15:07:25 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

static int	get_port(char *port_str)
{
	int		port;

	if (!(port = ft_atoi(port_str)) && port_str[0] != '0')
		return (-1);
	return (port);
}

static int	get_connection_socket(char *port_str)
{
	int		port;
	int		connection_socket;

	if ((port = get_port(port_str)) == -1
		|| (connection_socket = create_conn_sock(port)) == -1)
		return (-1);
	return (connection_socket);
}

int main(int argc, char **argv)
{
	int	connection_socket;

	if (argc != 2
		|| (connection_socket = get_connection_socket(argv[1])) == -1
		|| prompt_serv_pass(0) == EXIT_FAILURE) 
	{
		ft_printf("Usage: server port\n");
		return (EXIT_FAILURE);
	}
	if (select_loop(connection_socket) == EXIT_FAILURE)
		ft_printf("FAILED\n");
	return (EXIT_SUCCESS);
}
