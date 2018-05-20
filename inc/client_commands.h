/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_commands.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 21:32:37 by satkins           #+#    #+#             */
/*   Updated: 2018/05/19 16:07:26 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_COMMANDS_H

# define CLIENT_COMMANDS_H

extern t_client_prompt	g_prompt;

typedef struct		s_client_funcs
{
	char			*command;
	int				(*func)(int server_socket, char *param);
}					t_client_funcs;

int					send_nick(int server_socket, char *nick);
int					join(int server_socket, char *param);
int					color(int server_socket, char *param);

#endif