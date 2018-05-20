/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_to_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 14:48:34 by satkins           #+#    #+#             */
/*   Updated: 2018/05/19 14:49:35 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcap_utils.h"

int	move_to_prompt(int prompt_len)
{
	term_cm(g_window.ws_row, prompt_len);
	return (EXIT_SUCCESS);
}