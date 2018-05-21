/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 16:45:27 by satkins           #+#    #+#             */
/*   Updated: 2018/05/20 19:15:33 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client_obj.h"
#include "ft_irc.h"

/*
** Set a client object's color 
*/

static int	set_color(t_client client, char *param)
{
	int		color_num;

	if ((color_num = ft_ahtoi(param)) == -1)
		return (EXIT_FAILURE);
	ft_printf("color num: %d\n", color_num);
	client.vtable->set_color(client, color_num);
	return (EXIT_SUCCESS);
}

static int	send_resp(int client_socket)
{
	char	buff[1024];

	ft_bzero(buff, sizeof(buff));
	ft_strcpy(buff, "COLOR");
	if (send(client_socket, buff, sizeof(buff), 0) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	send_failure(int client_socket)
{
	char buff[1024];

	ft_bzero(buff, sizeof(buff));
	ft_strcpy(buff, "ERR_BADCOLOR");
	if (send(client_socket, buff, sizeof(buff), 0) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int			color(int client_socket, char *msg)
{
	if (set_color(g_client_tab[client_socket], ft_strchr(msg, ' ') + 1) == EXIT_FAILURE)
		send_failure(client_socket);
	else if (send_resp(client_socket) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
