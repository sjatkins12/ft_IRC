/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 11:59:33 by satkins           #+#    #+#             */
/*   Updated: 2018/05/20 17:13:24 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_H

# define FT_IRC_H

# include "libft.h"
# include "fd_set_utils.h"
# include "client.h"

# include <sys/socket.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/stat.h>
# include <signal.h>
# include <sys/select.h>
# include <sys/un.h>

# define MAX_NICK 9
# define MAX_PASS 50

typedef struct sockaddr_in	t_sockaddr_in;
typedef struct sockaddr_un	t_sockaddr_un;
typedef struct sockaddr		t_sockaddr;

typedef struct				s_color
{
	uint16_t				red;
	uint16_t				green;
	uint16_t				blue;	
}							t_color;

typedef struct				s_client_prompt
{
	char					nickname[MAX_NICK + 1];
	char					channel[30];
	int						channel_set;
	int						prompt_len;
}							t_client_prompt;

/*
** SERVER FUNCTIONS
*/

int							create_conn_sock(int port);
int							check_closed_socket(int clientfd, fd_set *cpy);
int							select_loop(int connection_sock);
int							accept_new_client(int master_fd, fd_set *cpy);
int							get_client_msg(int client_socket);
int 						prompt_serv_pass(int fd);
int							check_pwd(t_client *client, char *pwd);
int							set_nick(t_client client, char *nickname);
int							send_channel_msg(t_client client, char *msg);
int							close_client(int client_socket);

/*
** CLIENT FUNCTIONS
*/

int							create_client_sock(int port, char *host);
int							prompt_pass(int server_socket);
t_client_prompt				init_prompt(void);
int							print_prompt(t_client_prompt prompt);
int							read_channel(int server_socket);
int							clear_prompt(void);
int							move_to_prompt(int prompt_len);
int							handle_command(int server_socket, char *command);
int							connect_to_server(int port, char *host);



void						echo_off(void);
void						reset_tty(void);
t_color						split_color(int color_num);

#endif
