/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_pass.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 14:37:57 by satkins           #+#    #+#             */
/*   Updated: 2018/05/17 17:47:48 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"
#include "client_obj.h"

char	*g_pwd_path = NULL;

static int	set_pwd_path()
{
	if (!(g_pwd_path = ft_strnew(ft_strlen(getenv("HOME")) +
		ft_strlen("/.irc_pwd") + 1)))
		return (EXIT_FAILURE);
	ft_strcpy(g_pwd_path, getenv("HOME"));
	ft_strcat(g_pwd_path, "/.irc_pwd");
	return (EXIT_SUCCESS);
}

int prompt_serv_pass(int fd)
{
	char		*pass;

	if (g_pwd_path == NULL && set_pwd_path() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (fd == 0 &&
		(fd = open(g_pwd_path, O_RDWR | O_CREAT | O_EXCL, 0644)) < 0)
		return (EXIT_SUCCESS);
	ft_printf("Enter Server Password: ...");	
	echo_off();
	pass = NULL;
	if (get_next_line(STDIN_FILENO, &pass) <= 0)
		return (EXIT_FAILURE);
	reset_tty();
	ft_printf("\n");
	write(fd, pass, ft_strlen(pass));
	free(pass);
	close(fd);
	return (EXIT_SUCCESS);
}

int	check_pwd(t_client *client, char *pwd)
{
	int		fd;
	char	mem_pwd[MAX_PASS + 1];

	if (g_pwd_path == NULL && set_pwd_path() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_bzero(mem_pwd, sizeof(mem_pwd));
	if ((fd = open(g_pwd_path, O_RDWR | O_CREAT | O_EXCL, 0644)) < 0)
	{
		if ((fd = open(g_pwd_path, O_RDONLY)) < 0
			|| read(fd, mem_pwd, MAX_PASS) < 0
			|| !ft_strequ(pwd, mem_pwd))
			return (EXIT_FAILURE);
		close(fd);
		client->pword_registered = 1;
		return (EXIT_SUCCESS);
	}
	prompt_serv_pass(fd);
	check_pwd(client, pwd);
	return (EXIT_SUCCESS);
}

int		pass(int client_socket, char *msg)
{
	if (check_pwd(&(g_client_tab[client_socket]),
		ft_strchr(msg, ' ') + 1) == EXIT_FAILURE)
	{
		send(client_socket, "ERR_BADPASS", 13, 0);
		return (EXIT_FAILURE);
	}
	if (send(client_socket, "GOOD_PASS", 9, 0) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
