/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 16:03:21 by satkins           #+#    #+#             */
/*   Updated: 2018/05/20 19:33:39 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"
#include "color.h"

t_preset_color	g_colors[] = {
	{"RED", "0xff0000"},
	{"PINK", "0xff00ff"},
	{"GREEN", "0x00ff00"},
	{"BLACK", "0x000000"},
	{"BLUE", "0x0000ff"},
	{"CYAN", "0x00ffff"},
	{"PURPLE", "0x7f00ff"},
	{"YELLOW", "0xffff00"},
	{"ORANGE", "0xff8000"},
	{"WHITE", "0xffffff"},
	{"GRAY", "0x808080"},
	{"GREY", "0x808080"},
	{"", ""}
};

static char	*check_preset(char *param)
{
	int		i;

	ft_toupper_str(param);
	i = 0;
	while (g_colors[i].color[0])
	{
		if (ft_strequ(g_colors[i].color, param))
			return (g_colors[i].color_num);
		i++;
	}
	return (NULL);
}

static int	send_color(int server_socket, char *color_str)
{
	char	buff[1024];

	ft_bzero(buff, sizeof(buff));
	ft_strcpy(buff, "COLOR ");
	ft_strcat(buff, color_str);
	clear_prompt();
	if (send(server_socket, buff, sizeof(buff), 0) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	recv_resp(int server_socket)
{
	char	buff[1024];

	ft_bzero(buff, sizeof(buff));
	if (recv(server_socket, buff, sizeof(buff), 0) == -1)
		return (EXIT_FAILURE);
	if (!ft_strequ("COLOR", buff))
		ft_printf(RED "Error: %s\n" RES, buff);
	else
		ft_printf(CYAN "Color has changed!\n" RES);
	return (EXIT_SUCCESS);
}

int		color(int server_socket, char *param)
{
	char	*color_num;

	if ((color_num = check_preset(param)))
		param = color_num;
	if (send_color(server_socket, param) == EXIT_FAILURE
		|| recv_resp(server_socket) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
