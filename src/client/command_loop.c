/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 15:30:52 by satkins           #+#    #+#             */
/*   Updated: 2018/05/20 20:57:52 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"
#include "termcap_utils.h"

t_client_prompt	g_prompt;

int			undo_return(void)
{
	clear_prompt();
	term_cm(0, 0);
	scroll_r();
	cursor_ll();
	return (EXIT_SUCCESS);
}

int			send_msg_to_channel(int server_socket, char *command)
{
	clear_prompt();
	if (send(server_socket, command, 1024, 0) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	read_user_input(int server_socket)
{
	char	*command;

	command = NULL;
	if (get_next_line(STDIN_FILENO, &command) > 0)
	{
		if (!command)
			return (EXIT_FAILURE);
		if (command[0] == '/')
			handle_command(server_socket, command);
		else if (command[0] == '\0')
			undo_return();
		else if (g_prompt.channel_set && ft_strlen(command))
			send_msg_to_channel(server_socket, command);
		free(command);
		g_prompt.prompt_len = print_prompt(g_prompt);
	}
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
			read_user_input(server_socket);
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
