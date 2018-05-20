/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_termcaps.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 09:45:33 by satkins           #+#    #+#             */
/*   Updated: 2018/05/18 11:29:58 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcap_utils.h"
#include <sys/ioctl.h>

t_winsize		g_window;

int	init_termcaps(void)
{
	char	*term_buff;

	if (!(term_buff = ft_memalloc(3096))
		|| ioctl(0, TIOCGWINSZ, &g_window) < 0)
		return (EXIT_FAILURE);
	tgetent(term_buff, getenv("TERM"));
	clear_window();
	cursor_ll();
	return (EXIT_SUCCESS);
}
