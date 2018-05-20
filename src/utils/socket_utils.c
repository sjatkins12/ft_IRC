/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 13:46:35 by satkins           #+#    #+#             */
/*   Updated: 2018/05/19 20:52:14 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

int	create_conn_sock(int port)
{
	t_sockaddr_in	addr;
	int				sockfd;
	const int		op_val = 1;

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port);
	if (!(sockfd = socket(AF_INET, SOCK_STREAM, 6))
		|| setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &op_val, sizeof(int)) == -1
		|| setsockopt(sockfd, SOL_SOCKET,  SO_REUSEPORT, &op_val, sizeof(int)) == -1
		|| bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0
		|| listen(sockfd, 3) < 0)
		return (-1);
	return (sockfd);
}

int	create_client_sock(int port, char *host)
{
	t_sockaddr_in	serv_addr;
	int sockfd;

	ft_memset(&serv_addr, '0', sizeof(serv_addr));
	if ((serv_addr.sin_addr.s_addr = inet_addr(host)) == (in_addr_t)-1)
	{
		ft_printf("Usage: client port address\n");
		ft_printf("\tFor your host address 'dig +short `hostname`'\n");
		return (-1);
	}
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 6)) < 0)
		return (-1);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
		return (-1);
	return (sockfd);
}
