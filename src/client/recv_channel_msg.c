/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recv_channel_msg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 10:27:12 by satkins           #+#    #+#             */
/*   Updated: 2018/05/20 16:48:57 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcap_utils.h"
#include "ft_irc.h"
#include "msg.h"


t_msg_type_dis	g_msg_dis[] = {
	{"MSG", &channel_msg},
	// {"PRVMSG", &private_msg},
	{"SERVMSG", &server_msg},
	{"", NULL}
};

int			read_channel(int server_socket)
{
	char			buff[1024];
	char			*msg;
	t_msg_header	header;
	int				i;

	ft_bzero(buff, sizeof(buff));
	msg = &(buff[sizeof(t_msg_header)]);
	ft_bzero(&header, sizeof(t_msg_header));
	recv(server_socket, buff, sizeof(buff), 0);
	ft_memcpy(&header, buff, sizeof(t_msg_header));
	i = 0;
	while (g_msg_dis[i].msg_type[0])
	{
		if (ft_strequ(g_msg_dis[i].msg_type, header.msg_type))
			g_msg_dis[i].func(header, msg);
		i++;
	}
	return (EXIT_SUCCESS);
	
}

int			clear_prompt(void)
{
	move_up_line();
	delete_current_line();
	return (EXIT_SUCCESS);
}
