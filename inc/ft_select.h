/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:10:16 by satkins           #+#    #+#             */
/*   Updated: 2018/05/17 14:14:57 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H

# define FT_SELECT_H

#include "fd_set_utils.h"

typedef struct		s_select_dispatch
{
	int				new_connection_socket;
	int				(*accept_connection)(int conn_socket, fd_set *cpy);
	int				(*client_action)(int client_socket, fd_set *cpy);
}					t_select_dispatch;

#endif