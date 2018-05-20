/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 17:44:55 by satkins           #+#    #+#             */
/*   Updated: 2018/05/16 21:29:50 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_H

# define CHANNEL_H

# include "libft.h"

# define MAX_CHANNEL 40

typedef struct s_channel	t_channel;

typedef struct				s_channel_vtable
{
	void					(*add_member)(t_channel self, int client_id);
	void					(*remove_member)(t_channel self, int client_id);
	uint8_t					*(*get_channel_members)(t_channel self);
	int						(*get_num_members)(t_channel self);
	int						(*set_channel_name)(t_channel self, char *name);
	char					*(*get_channel_name)(t_channel self);
}							t_channel_vtable;

typedef struct	s_channel
{
	int						channel_id;
	const t_channel_vtable	*vtab;
}				t_channel;

t_channel	new_channel(void);

#endif
