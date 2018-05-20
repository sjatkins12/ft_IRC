/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 21:40:46 by satkins           #+#    #+#             */
/*   Updated: 2018/05/20 00:38:32 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"
#include "client_commands.h"

static int	recv_response(int server_socket, char *chan_name)
{
	char	buff[1024];

	ft_bzero(buff, sizeof(buff));
	if (recv(server_socket, buff, 1024, 0) == -1)
		return (EXIT_FAILURE);
	if (ft_strequ(buff, "JOIN"))
	{
		ft_printf("\033[1;34mJoined %s successfully\n\033[0m", chan_name);
		ft_bzero(g_prompt.channel, sizeof(g_prompt.channel));
		ft_strcpy(g_prompt.channel, chan_name);
		g_prompt.channel_set = 1;
	}
	else
		ft_printf("\033[1;31mFailed to join %s\n\033[0m", chan_name);
	return (EXIT_SUCCESS);
}

static int	send_command(int server_socket, char *chan_name)
{
	char	buff[1024];

	ft_bzero(buff, sizeof(buff));
	ft_strcpy(buff, "JOIN ");
	ft_strcat(buff, chan_name);
	if (send(server_socket, buff, 1024, 0) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		join(int server_socket, char *param)
{
	if (!param
		|| send_command(server_socket, param) == EXIT_FAILURE
		|| recv_response(server_socket, param) == EXIT_FAILURE)
		return (EXIT_FAILURE);	
	return (EXIT_SUCCESS);
}
