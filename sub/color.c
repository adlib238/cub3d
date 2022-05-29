/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 06:46:32 by kfumiya           #+#    #+#             */
/*   Updated: 2021/05/08 22:07:17 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	get_tex_color(t_tex *tex, t_pos *pos)
{
	if (pos->x >= 0 && pos->x < tex->width
		&& pos->y >= 0 && pos->y < tex->height)
	{
		return (*(int*)(tex->ptr
			+ (4 * tex->width * (int)pos->y)
			+ (4 * (int)pos->x)));
	}
	return (0x0);
}

int
	shade_color(int color, double divide)
{
	if (divide <= 1.)
		return (color);
	return (((int)(((0xFF0000 & color) >> 16) / divide) << 16)
		+ ((int)(((0x00FF00 & color) >> 8) / divide) << 8)
		+ ((int)((0x0000FF & color) / divide)));
}

int
	distance_shade(int options, int color, double distance)
{
	if (options & FLAG_SHADOWS)
		return (shade_color(color, distance / 1.5));
	return (color);
}
