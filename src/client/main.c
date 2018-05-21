/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 13:24:23 by satkins           #+#    #+#             */
/*   Updated: 2018/05/20 13:27:55 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"
#include "termcap_utils.h"


int			command_loop(int server_socket);

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