/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 18:39:21 by satkins           #+#    #+#             */
/*   Updated: 2018/05/19 18:48:35 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSG_H

# define MSG_H

#include "ft_irc.h"

typedef struct	s_msg_header
{
	char		nickname[10];
	t_color		color;
	int			hour;
	int			min;
}				t_msg_header;

#endif