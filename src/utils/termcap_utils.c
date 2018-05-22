/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 17:00:27 by satkins           #+#    #+#             */
/*   Updated: 2018/05/20 20:59:28 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcap_utils.h"

struct termios g_save;

static void	set_raw_mode(void)
{
	struct termios raw;

	tcgetattr(ttyslot(), &raw);
	g_save = raw;
	raw.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(ttyslot(), TCSANOW, &raw);
}

static void	reset(void)
{
	tcsetattr(ttyslot(), TCSANOW, &g_save);	
}

void		delete_current_line(void)
{
	static char	*cache = NULL;
	static char	*cachecr = NULL;

	if (cache == NULL)
		cache = tgetstr("cd", NULL);
	if (cachecr == NULL)
		cachecr = tgetstr("cr", NULL);
	set_raw_mode();
	tputs(cachecr, 1, &my_putchar);
	tputs(cache, 1, &my_putchar);
	reset();
}

void		move_up_line(void)
{
	static char	*cacheup = NULL;
	static char	*cachecr = NULL;
	
	if (cacheup == NULL)
		cacheup = tgetstr("up", NULL);
	if (cachecr == NULL)
		cachecr = tgetstr("cr", NULL);
	set_raw_mode();
	tputs(cacheup, 1, &my_putchar);
	tputs(cachecr, 1, &my_putchar);	
	reset();
}

void		move_down_line(void)
{
	static char	*cachedo = NULL;
	static char	*cachecr = NULL;
	
	if (cachedo == NULL)
		cachedo = tgetstr("do", NULL);
	if (cachecr == NULL)
		cachecr = tgetstr("cr", NULL);
	set_raw_mode();
	tputs(cachedo, 1, &my_putchar);
	tputs(cachecr, 1, &my_putchar);	
	reset();
}

void		scroll_f(void)
{
	static char	*cache = NULL;

	if (cache == NULL)
		cache = tgetstr("sf", NULL);	
	set_raw_mode();
	tputs(cache, 1, &my_putchar);
	reset();
}

void		save_cur(void)
{
	static char	*cache = NULL;

	if (cache == NULL)
		cache = tgetstr("sc", NULL);
	set_raw_mode();
	tputs(cache, 1, &my_putchar);
	reset();
}

void		restore_cur(void)
{
	static char	*cache = NULL;

	if (cache == NULL)
		cache = tgetstr("rc", NULL);
	set_raw_mode();
	tputs(cache, 1, &my_putchar);
	reset();
}

void		clear_window(void)
{
	static char	*cache = NULL;

	if (cache == NULL)
		cache = tgetstr("cl", NULL);
	set_raw_mode();
	tputs(cache, 1, &my_putchar);
	reset();
}

void		cursor_ll(void)
{
	static char	*cache = NULL;

	if (cache == NULL)
		cache = tgetstr("cm", NULL);
	set_raw_mode();
	tputs(tgoto(cache, 0, g_window.ws_row), 1, &my_putchar);
	reset();
}

void		term_cm(int y, int x)
{
	static char	*cache = NULL;

	if (cache == NULL)
		cache = tgetstr("cm", NULL);
	set_raw_mode();
	tputs(tgoto(cache, x, y), 1, &my_putchar);
	reset();
}

void		ring_bell(void)
{
	static char	*cache = NULL;

	if (cache == NULL)
		cache = tgetstr("bl", NULL);
	set_raw_mode();
	tputs(cache, 1, &my_putchar);
	reset();
}

void			scroll_r(void)
{
	static char	*cache = NULL;

	if (cache == NULL)
		cache = tgetstr("sr", NULL);	
	set_raw_mode();
	tputs(cache, 1, &my_putchar);
	reset();
}
