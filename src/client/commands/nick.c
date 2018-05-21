/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 14:53:29 by satkins           #+#    #+#             */
/*   Updated: 2018/05/20 15:39:39 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"
#include "client_commands.h"

static int	prompt_nick(int server_socket)
{
	char	*nick;

	ft_printf("NICKNAME MUST BE LESS THAN %d CHARS\n", MAX_NAME + 1);
	ft_printf("<RE-ENTER NICKNAME ...> ");
	nick = NULL;
	if (get_next_line(STDIN_FILENO, &nick) < 0)	
		return (EXIT_FAILURE);
	send_nick(server_socket, nick);
	free(nick);
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
		if (ft_strequ(buff, "ERR_NICKTOOLONG"))
			prompt_nick(server_socket);
		else
			return (EXIT_FAILURE);
	}
	else
	{
		if (g_prompt.nickname[0])
			ft_printf("%s NOW %s\n", g_prompt.nickname, nick);
		else
			ft_printf("Nickname: %s\n", nick);
		ft_bzero(g_prompt.nickname, sizeof(g_prompt.nickname));
		ft_strcpy(g_prompt.nickname, nick);
	}
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