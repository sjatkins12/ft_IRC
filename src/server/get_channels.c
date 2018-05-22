/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_channels.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 14:29:32 by satkins           #+#    #+#             */
/*   Updated: 2018/05/22 15:09:21 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"
#include "channel_obj.h"

int	get_channels(__attribute__((unused))int client_id, __attribute__((unused))char *msg)
{
	t_channel	chan;
	char		buff[1024];
	int			i;

	ft_bzero(buff, sizeof(buff));
	ft_strcat(buff, "CHAN ");
	i = 0;
	while (i < MAX_CHANNEL)
	{
		chan = g_channel_tab[i];
		if (!chan.vtab)
			break ;
		ft_strcat(buff, "\n");
		ft_strcat(buff, chan.vtab->get_channel_name(chan));
		i++;
	}
	if (i == 0)
		send(client_id, "ERR_NOCHAN", 10, 0);
	else
		send(client_id, buff, sizeof(buff), 0);
	return (EXIT_SUCCESS);
}
