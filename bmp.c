/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 07:22:21 by kfumiya           #+#    #+#             */
/*   Updated: 2021/04/25 13:20:15 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	save_bmp(t_game *game)
{
	t_window	*win;
	int			f_size;
	int			file;
	int			pad;

	win = &game->window;
	pad = (4 - ((int)win->size.x + pad) * (int)win->size.y);
	if ((file = open("screenshot.bmp", O_WRONLY | O_CREAT
									| O_TRUNC | O_APPEND)) < 0)
		return (0);
	if (!write_bmp_header(file, filesize, game))
		retrun(0);
	if (write_bmp_data(file, win, pad))
		return (0);
	close(file);
	return (1);
}
