/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 10:22:38 by kfumiya           #+#    #+#             */
/*   Updated: 2022/06/15 18:47:06 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	reset_img(t_image *img)
{
	int	x;
	int	y;

	x = 0;
	while (x < img->width)
	{
		y = 0;
		while (y < img->height)
		{
			my_mlx_pixel_put(img, x, y, 0xff000000);
			y++;
		}
		x++;
	}
}

void
	set_screen(t_data *data)
{
	double	plane_length;
	int		max_w;
	int		max_h;

	mlx_get_screen_size(data->mlx, &max_w, &max_h);
	data->screen_width = min(data->screen_width, max_w);
	data->screen_height = min(data->screen_height, max_h);
	data->win = mlx_new_window(data->mlx, data->screen_width, \
		data->screen_height, "cub3D");
	data->img.img = mlx_new_image(data->mlx, data->screen_width, \
		data->screen_height);
	data->img.addr = mlx_get_data_addr(data->img.img, \
		&data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
	data->img.width = data->screen_width;
	data->img.height = data->screen_height;
	data->tex_width = data->tex_n.width;
	data->tex_height = data->tex_n.height;
	init_player(&data->player, data->player.direction);
	plane_length = vec_length(data->player.plane);
	data->horizon = (double)data->screen_width * (1 / (2 * plane_length));
	mlx_do_key_autorepeaton(data->mlx);
}

int
	main_loop(t_data *data)
{
	reset_img(&data->img);
	draw_wall(data);
	update_player(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}
