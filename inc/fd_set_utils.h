/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_set_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 13:09:55 by satkins           #+#    #+#             */
/*   Updated: 2018/05/17 15:51:08 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FD_SET_UTILS_H

# define FD_SET_UTILS_H

#include <sys/select.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

typedef struct	s_fd_sets
{
	fd_set		*fds;
	fd_set		*cpy;
}				t_fd_sets;

void			create_sets(t_fd_sets sets, int fd);
t_fd_sets		set_constructor();
void			reset_fd_set(t_fd_sets sets);
void			set_destructor(t_fd_sets sets);
int				check_closed_socket(int fd, fd_set *cpy);

#endif