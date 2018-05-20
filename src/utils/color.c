/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 16:13:43 by satkins           #+#    #+#             */
/*   Updated: 2018/05/19 16:16:26 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

t_color		split_color(int color_num)
{
	t_color	color;

	ft_bzero(&color, sizeof(t_color));
	if (color_num < 0)
		return (color);
	color.blue = color_num & 0xFF;
	color.green = (color_num >> 8) & 0xFF;
	color.red = (color_num >> 16) & 0xFF;
	return (color);
}