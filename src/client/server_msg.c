/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_msg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 16:50:16 by satkins           #+#    #+#             */
/*   Updated: 2018/05/20 17:15:09 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcap_utils.h"
#include "ft_irc.h"
#include "msg.h"

t_client_prompt	g_prompt;

int		server_msg(__attribute__((unused))t_msg_header header, char *msg)
{
	move_to_prompt(g_prompt.prompt_len);
	save_cur();
	delete_current_line();
	ft_printf("%s\n", msg);
	print_prompt(g_prompt);
	restore_cur();
	return (EXIT_SUCCESS);
}
