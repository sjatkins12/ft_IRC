/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_terminal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 19:55:24 by satkins           #+#    #+#             */
/*   Updated: 2018/05/17 17:48:01 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include "libft.h"

struct termios g_save;

void	echo_off(void)
{
	struct termios necho;

	tcgetattr(ttyslot(), &necho);
	g_save = necho;
	necho.c_lflag &= ~ECHO;
	tcsetattr(ttyslot(), TCSANOW, &necho);

}

void	reset_tty(void)
{
	tcsetattr(ttyslot(), TCSANOW, &g_save);
}
