/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 00:16:03 by satkins           #+#    #+#             */
/*   Updated: 2018/05/20 00:51:40 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"
#include "client_commands.h"

static int	print_list(char *list)
{
	char	*next;

	while ((next = ft_strchr(list, '\n')))
	{
		ft_putnstr(list, next - list);
		ft_putchar('\n');
		list = next + 1;
	}
	return (EXIT_SUCCESS);
}

int	who(int server_socket, __attribute__((unused))char *param)
{
	char	buff[1024];

	ft_bzero(buff, sizeof(buff));
	ft_strcpy(buff, "WHO\0");
	if (send(server_socket, buff, sizeof(buff), 0) == -1)
		return (EXIT_FAILURE);
	ft_bzero(buff, sizeof(buff));
	if (recv(server_socket, buff, sizeof(buff), 0) == -1)
		return (EXIT_FAILURE);
	if (ft_strncmp("WHO ", buff, 4))
	{
		ft_printf("You need to be in a channel to use /who ;)\n");
		return (EXIT_SUCCESS);
	}
	print_list(ft_strchr(buff, ' ') + 1);
	return (EXIT_SUCCESS);
}
