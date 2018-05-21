/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 18:39:21 by satkins           #+#    #+#             */
/*   Updated: 2018/05/20 17:13:29 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSG_H

# define MSG_H

#include "ft_irc.h"
#include "color.h"

typedef struct	s_msg_header
{
	char		msg_type[8];
	char		nickname[10];
	t_color		color;
	int			hour;
	int			min;
}				t_msg_header;

typedef struct	s_msg_type_dis
{
	char		msg_type[7];
	int			(*func)(t_msg_header header, char *msg);
}				t_msg_type_dis;

int							channel_msg(t_msg_header header, char *msg);
int							server_msg(t_msg_header header, char *msg);

#endif