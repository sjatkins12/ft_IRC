/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_channels.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 14:20:30 by satkins           #+#    #+#             */
/*   Updated: 2018/05/22 15:09:16 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"
#include "client_commands.h"

static int	recv_channels(int server_socket)
{
	char	buff[1024];

	ft_bzero(buff, sizeof(buff));
	if (recv(server_socket, buff, sizeof(buff), 0) == -1)
		return (EXIT_FAILURE);
	if (ft_strnequ("CHAN ", buff, 5))
		ft_printf(CYAN "Channels:%s\n" RES, ft_strchr(buff, ' ') + 1);
	else
		ft_printf("No Channels\n");
	return (EXIT_SUCCESS);
}

static int	send_req_chan(int server_socket)
{
	char	buff[1024];

	ft_bzero(buff, sizeof(buff));
	ft_strcpy(buff, "CHAN ");
	if (send(server_socket, buff, sizeof(buff), 0) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	get_channels(int server_socket, __attribute__((unused))char *param)
{
	if (send_req_chan(server_socket) == EXIT_FAILURE
		|| recv_channels(server_socket) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
