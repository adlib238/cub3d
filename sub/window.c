/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 08:56:02 by kfumiya           #+#    #+#             */
/*   Updated: 2021/06/06 01:30:02 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	clear_window(t_window *window)
{
	if (window->screen.img)
		mlx_destroy_image(window->ptr, window->screen.img);
	if (window->ptr && window->win)
		mlx_destroy_window(window->ptr, window->win);
	return (0);
}

int
	init_image(t_window *window, t_image *img)
{
	if (!(img->img =
		mlx_new_image(window->ptr, window->size.x, window->size.y)))
		return (0);
	img->ptr = mlx_get_data_addr(
		img->img, &img->bpp, &img->size_line, &img->endian);
	return (1);
}

int
	init_window(t_window *window, t_config *config)
{
	int			x;
	int			y;
	t_window	*win;

	mlx_get_screen_size(&win->ptr, &x, &y);
	(config->requested_width <= x) ? x = config->requested_width : x;
	(config->requested_height <= y) ? y = config->requested_height : y;
	set_pos(&window->size, x, y);
	window->ptr = NULL;
	window->win = NULL;
	window->screen.img = NULL;
	if (!(window->ptr = mlx_init())
		|| !(window->win = mlx_new_window(
			window->ptr, window->size.x, window->size.y, "cub3d")))
		return (0);
	if (!init_image(window, &window->screen))
		return (0);
	return (1);
}

void
	update_window(t_game *game)
{
	t_window	*win;

	win = &game->window;
	mlx_put_image_to_window(win->ptr, win->win, win->screen.img, 0, 0);
}
