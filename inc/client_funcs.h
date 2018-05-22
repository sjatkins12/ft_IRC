/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_funcs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 19:43:10 by satkins           #+#    #+#             */
/*   Updated: 2018/05/21 14:29:14 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_FUNCS_H

# define CLIENT_FUNCS_H

typedef struct	s_client_funcs
{
	char		*command;
	int			(*func)(int client_socket, char *msg);
}				t_client_funcs;

int				nickname(int client_socket, char *msg);
int				pass(int client_socket, char *msg);
int				join(int client_id, char *msg);
int 			color(int client_socket, char *msg);
int				who(int	client_id, char *msg);
int				get_channels(int client_id, char *msg);

#endif
