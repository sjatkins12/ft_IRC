/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 17:08:55 by satkins           #+#    #+#             */
/*   Updated: 2018/05/20 20:33:32 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMCAP_UTILS_H

# define TERMCAP_UTILS_H

#include <termios.h>
#include <term.h>
#include "libft.h"

typedef struct winsize	t_winsize;

extern t_winsize		g_window;

int			my_putchar(int chrr);
void		delete_current_line(void);
void		move_up_line(void);
void		move_down_line(void);
void		save_cur(void);
void		restore_cur(void);
void		scroll_f(void);
void		clear_window(void);
void		cursor_ll(void);
void		term_cm(int y, int x);
void		ring_bell(void);
void		scroll_r(void);

int			init_termcaps(void);

#endif