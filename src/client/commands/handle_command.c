/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 13:10:46 by satkins           #+#    #+#             */
/*   Updated: 2018/05/20 13:11:44 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"
#include "client_commands.h"

t_client_funcs	g_client_commands[] = {
				{"/nick ", &send_nick},
				{"/join ", &join},
				{"/color ", &color},
				{"/who\0", &who},
				{NULL, NULL}
};

int	handle_command(int server_socket, char *command)
{
	int				i;
	t_client_funcs	tuple;

	i = 0;
	while (g_client_commands[i].command)
	{
		tuple = g_client_commands[i];
		if (ft_strnequ(tuple.command, command, ft_strlen(tuple.command)))
			return (tuple.func(server_socket, ft_strchr(command, ' ') + 1));
		i++;
	}
	return (EXIT_SUCCESS);
}
