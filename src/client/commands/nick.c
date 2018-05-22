/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 14:53:29 by satkins           #+#    #+#             */
/*   Updated: 2018/05/22 14:05:16 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"
#include "client_commands.h"

static int	prompt_nick(char *buff)
{
	ft_printf("Bad Nickname. Use \"/nick <nickname>\" to change it.\n");
	if (ft_strequ(buff, "ERR_NICKTOOLONG"))
		ft_printf(RED "NICKNAME MUST BE LESS THAN %d CHARS\n" RES, MAX_NAME + 1);
	else if (ft_strequ(buff, "ERR_NICKCOLLISION"))
		ft_printf(RED "NICKNAME IS IN USE\n" RES);
	return (EXIT_SUCCESS);
}

static int	send_command(int server_socket, char *nick)
{
	char	buff[1024];

	ft_bzero(buff, sizeof(buff));
	ft_strcpy(buff, "NICK ");
	ft_strcat(buff, nick);
	clear_prompt();
	if (send(server_socket, buff, sizeof(buff), 0) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	recv_response(int server_socket, char *nick)
{
	char buff[1024];

	ft_bzero(buff, sizeof(buff));
	if (recv(server_socket, buff, sizeof(buff), 0) == -1)
		return (EXIT_FAILURE);
	if (!ft_strequ(buff, "NICK"))
	{
		prompt_nick(buff);
		return (EXIT_SUCCESS);
	}
	if (g_prompt.nickname[0])
		ft_printf("%s NOW %s\n", g_prompt.nickname, nick);
	else
		ft_printf("Nickname: %s\n", nick);
	ft_bzero(g_prompt.nickname, sizeof(g_prompt.nickname));
	ft_strcpy(g_prompt.nickname, nick);
	return (EXIT_SUCCESS);
}

int		send_nick(int server_socket, char *nick)
{
	if (!nick
		|| send_command(server_socket, nick) == EXIT_FAILURE
		|| recv_response(server_socket, nick) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}