/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_termcaps.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 09:45:33 by satkins           #+#    #+#             */
/*   Updated: 2018/05/22 15:33:16 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcap_utils.h"
#include <sys/ioctl.h>

t_winsize		g_window;

int	get_window_size(void)
{
 	if (ioctl(0, TIOCGWINSZ, &g_window) < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	init_termcaps(void)
{
	char	*term_buff;

	if (!(term_buff = ft_memalloc(3096))
		|| get_window_size() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	tgetent(term_buff, getenv("TERM"));
	clear_window();
	cursor_ll();
	return (EXIT_SUCCESS);
}
