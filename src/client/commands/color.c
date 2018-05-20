/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 16:03:21 by satkins           #+#    #+#             */
/*   Updated: 2018/05/19 16:43:30 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

static int	send_color(int server_socket, char *color_str)
{
	char	buff[1024];

	ft_bzero(buff, sizeof(buff));
	ft_strcpy(buff, "COLOR ");
	ft_strcat(buff, color_str);
	if (send(server_socket, buff, sizeof(buff), 0) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
	
}

static int	recv_resp(int server_socket)
{
	char	buff[1024];

	ft_bzero(buff, sizeof(buff));
	if (recv(server_socket, buff, sizeof(buff), 0) == -1
		|| !ft_strequ("COLOR", buff))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		color(int server_socket, char *param)
{
	int	color_num;

	color_num = ft_ahtoi(param);
	set_prompt_color(color_num);
	if (send_color(server_socket, param) == EXIT_FAILURE
		|| recv_resp(server_socket) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
