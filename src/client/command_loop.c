/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 15:30:52 by satkins           #+#    #+#             */
/*   Updated: 2018/05/20 00:14:46 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"
#include "client_commands.h"
#include "termcap_utils.h"

t_client_funcs	g_client_commands[] = {
				{"/nick ", &send_nick},
				{"/join ", &join},
				{"/color ", &color},
				{"/who\0", &who},
				{NULL, NULL}
};

t_client_prompt	g_prompt;

static int	handle_command(int server_socket, char *command)
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

int			send_msg_to_channel(int server_socket, char *command)
{
	clear_prompt();
	if (send(server_socket, command, ft_strlen(command), 0) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int			set_prompt_color(int color_num)
{
	t_color	color;

	color = split_color(color_num);
	g_prompt.self_color.blue = color.blue;
	g_prompt.self_color.red = color.red;
	g_prompt.self_color.green = color.green;
	return (EXIT_SUCCESS);
}

int			command_loop(int server_socket)
{
	char			*command;
	t_fd_sets		sets;

	sets = set_constructor();
	create_sets(sets, server_socket);
	FD_SET(STDIN_FILENO, sets.cpy);
	reset_fd_set(sets);
	command = NULL;
	g_prompt = init_prompt();
	while (1)
	{
		if (select(FD_SETSIZE, sets.fds, NULL, NULL, NULL) == -1)
			return (EXIT_FAILURE);
		if (FD_ISSET(STDIN_FILENO, sets.fds))
		{
			if (get_next_line(STDIN_FILENO, &command) > 0)
			{
				if (!command)
					return (EXIT_FAILURE);
				if (command[0] == '/')
					handle_command(server_socket, command);
				else if (g_prompt.channel_set && ft_strlen(command))
					send_msg_to_channel(server_socket, command);
				free(command);
				g_prompt.prompt_len = print_prompt(g_prompt);
			}
			command = NULL;
		}
		if (FD_ISSET(server_socket, sets.fds))
		{
			if (check_closed_socket(server_socket, sets.cpy) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			read_channel(server_socket);
		}
		reset_fd_set(sets);
	}
	return (EXIT_SUCCESS);
}
