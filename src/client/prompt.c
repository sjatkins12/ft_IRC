/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 22:12:45 by satkins           #+#    #+#             */
/*   Updated: 2018/05/19 18:27:07 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

t_client_prompt	init_prompt(void)
{
	t_client_prompt	prompt;

	ft_bzero(&prompt, sizeof(t_client_prompt));
	ft_strcpy(prompt.channel, "No Channel");
	ft_strcpy(prompt.nickname, getenv("USER"));
	prompt.channel_set = 0;
	prompt.prompt_len = print_prompt(prompt);
	prompt.self_color = split_color(DEFAULT_COLOR);
	return (prompt);
}

int				print_prompt(t_client_prompt prompt)
{
	return (ft_printf("<CH: %s> %s ...", prompt.channel, prompt.nickname));
}
