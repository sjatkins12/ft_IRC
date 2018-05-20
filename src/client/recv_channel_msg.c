/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recv_channel_msg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 10:27:12 by satkins           #+#    #+#             */
/*   Updated: 2018/05/20 00:50:11 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcap_utils.h"
#include "ft_irc.h"
#include "msg.h"

t_client_prompt	g_prompt;

void		print_user(t_msg_header header)
{
	ft_printf("%s: %02d:%02d\n", header.nickname, header.hour, header.min);
}

int			read_channel(int server_socket)
{
	char			buff[1024];
	char			*msg;
	t_msg_header	header;

	ft_bzero(buff, sizeof(buff));
	msg = &(buff[sizeof(t_msg_header)]);
	ft_bzero(&header, sizeof(t_msg_header));
	recv(server_socket, buff, sizeof(buff), 0);
	ft_memcpy(&header, buff, sizeof(t_msg_header));
	if (ft_strncmp(g_prompt.nickname, header.nickname, ft_strlen(g_prompt.nickname)))
	{
		move_to_prompt(g_prompt.prompt_len);
		save_cur();
		delete_current_line();
		print_user(header);
		ft_printf("\033[38;2;%d;%d;%dm%s\n\033[0m", header.color.red, header.color.green, header.color.blue, msg);
		print_prompt(g_prompt);
		restore_cur();
	}
	else
	{
		delete_current_line();
		print_user(header);		
		ft_printf("\033[38;2;%d;%d;%dm%s\033[0m", header.color.red, header.color.green, header.color.blue, msg);
		move_down_line();
		print_prompt(g_prompt);
	}
	return (EXIT_SUCCESS);
}

int			clear_prompt(void)
{
	move_up_line();
	delete_current_line();
	return (EXIT_SUCCESS);
}
