/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel_msg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 16:46:52 by satkins           #+#    #+#             */
/*   Updated: 2018/05/20 16:48:36 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcap_utils.h"
#include "ft_irc.h"
#include "msg.h"

t_client_prompt	g_prompt;

static void		print_user(t_msg_header header)
{
	ft_printf("%s: %02d:%02d\n", header.nickname, header.hour, header.min);
}

int		channel_msg(t_msg_header header, char *msg)
{
	static char		*last_user = NULL;
	
	if (ft_strncmp(g_prompt.nickname, header.nickname, ft_strlen(g_prompt.nickname)))
	{
		move_to_prompt(g_prompt.prompt_len);
		ring_bell();
		save_cur();
		delete_current_line();
		if (!last_user || ft_strcmp(last_user, header.nickname))
			print_user(header);
		ft_printf("\033[38;2;%d;%d;%dm%s\n\033[0m", header.color.red, header.color.green, header.color.blue, msg);
		print_prompt(g_prompt);
		restore_cur();
		free(last_user);
		if (!(last_user = ft_strdup(header.nickname)))
			return (EXIT_FAILURE);
	}
	else
	{
		delete_current_line();
		if (!last_user || ft_strcmp(last_user, header.nickname))
			print_user(header);		
		ft_printf("\033[38;2;%d;%d;%dm%s\033[0m", header.color.red, header.color.green, header.color.blue, msg);
		move_down_line();
		print_prompt(g_prompt);
		free(last_user);
		if (!(last_user = ft_strdup(header.nickname)))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}