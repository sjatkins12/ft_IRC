/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 13:20:17 by satkins           #+#    #+#             */
/*   Updated: 2018/05/18 11:05:03 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

#include <termios.h>

static int	print_pwd_prompt(void)
{
	ft_printf("Enter Password: ...");
	echo_off();
	return (EXIT_SUCCESS);

}

static int	send_pass(int server_socket, char *pass)
{
	char	buff[1024];
	if (!pass || ft_strlen(pass) > MAX_PASS)
		return (EXIT_FAILURE);
	ft_bzero(buff, sizeof(buff));
	ft_strcpy(buff, "PASS ");
	ft_strcat(buff, pass);
	if (send(server_socket, buff, sizeof(buff), 0) == -1)
		return (EXIT_FAILURE);
	ft_bzero(buff, sizeof(buff));
	if (recv(server_socket, buff, sizeof(buff), 0) == -1)
		return (EXIT_FAILURE);
	if (!ft_strequ(buff, "GOOD_PASS"))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		prompt_pass(int server_socket)
{
	int		ret;
	char	*pass;

	ret = EXIT_FAILURE;
	while (ret == EXIT_FAILURE)
	{
		pass = NULL;
		print_pwd_prompt();
		if (get_next_line(STDIN_FILENO, &pass) <= 0)
			return (EXIT_FAILURE);
		reset_tty();
		ft_printf("\n");
		ret = send_pass(server_socket, pass);
		free(pass);
	}
	ft_printf("\033[1;32mConnected!\n\033[0m");
	return (EXIT_SUCCESS);
}