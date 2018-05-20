/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 13:49:56 by satkins           #+#    #+#             */
/*   Updated: 2018/05/19 19:54:48 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H

# define CLIENT_H

#include <sys/types.h>
#define MAX_NAME 9
# define DEFAULT_COLOR 424242

typedef struct s_client		t_client;

typedef struct				s_client_vtable
{
	void					(*set_nickname)(t_client self, char *name);
	char					*(*get_nickname)(t_client self);
	void					(*set_channel)(t_client self, int channel_id);
	int						(*get_channel)(t_client self);
	void					(*set_color)(t_client self, int color);
	int						(*get_color)(t_client self);
}							t_client_vtable;

typedef struct				s_client
{
	int						client_id;
	int						pword_registered : 1;
	const t_client_vtable	*vtable;
}							t_client;
t_client					new_client(int id);

#endif
