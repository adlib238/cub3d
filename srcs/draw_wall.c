/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 20:08:16 by kfumiya           #+#    #+#             */
/*   Updated: 2022/06/17 10:00:02 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	init_ray(t_data *data, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)data->screen_width - 1;
	ray->dir.x = data->player.dir.x + data->player.plane.x * ray->camera_x;
	ray->dir.y = data->player.dir.y + data->player.plane.y * ray->camera_x;
	ray->map_x = (int)data->player.pos.x;
	ray->map_y = (int)data->player.pos.y;
	ray->delta_dist_x = fabs(1 / ray->dir.x);
	ray->delta_dist_y = fabs(1 / ray->dir.y);
	ray->step_x = 1;
	ray->side_dist_x = (ray->map_x + 1.0 - data->player.pos.x)
		* ray->delta_dist_x;
	ray->step_y = 1;
	ray->side_dist_y = (ray->map_y + 1.0 - data->player.pos.y)
		* ray->delta_dist_y;
	if (ray->dir.x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (data->player.pos.x - ray->map_x)
			* ray->delta_dist_x;
	}
	if (ray->dir.y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (data->player.pos.y - ray->map_y)
			* ray->delta_dist_y;
	}
}

static void
	raycast(t_data *data, t_ray *ray)
{
	while (data->cubfile->map[ray->map_y][ray->map_x] != '1')
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
	}
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - data->player.pos.x \
			+ (1 - ray->step_x) / 2) / ray->dir.x;
	else
		ray->perp_wall_dist = (ray->map_y - data->player.pos.y \
			+ (1 - ray->step_y) / 2) / ray->dir.y;
	set_texture(data, ray);
}

static void
	cal_screen_info(t_data *data, t_ray ray, t_wall *wall)
{
	wall->line_height = (int)(data->horizon / ray.perp_wall_dist);
	wall->draw_start = -wall->line_height / 2 + data->screen_height / 2;
	if (wall->draw_start < 0)
		wall->draw_start = 0;
	wall->draw_end = wall->line_height / 2 + data->screen_height / 2;
	if (wall->draw_end >= data->screen_height)
		wall->draw_end = data->screen_height - 1;
	if (ray.side == 0)
		wall->wall_x = data->player.pos.y + ray.perp_wall_dist * ray.dir.y;
	else
		wall->wall_x = data->player.pos.x + ray.perp_wall_dist * ray.dir.x;
	wall->wall_x -= floor(wall->wall_x);
	wall->texture_x = (int)(wall->wall_x * ray.tex->width);
	if ((ray.side == 0 && ray.dir.x < 0) || (ray.side == 1 && ray.dir.y > 0))
		wall->texture_x = ray.tex->width - wall->texture_x - 1;
	wall->step = 1.0 * ray.tex->height / (double)wall->line_height;
}

static void
	draw_stripe(t_data *data, t_ray ray, t_wall *wall, int x)
{
	uint32_t	color;
	int			y;

	wall->texture_pos_y = (wall->draw_start - data->screen_height / 2 \
		+ wall->line_height / 2) * wall->step;
	y = 0;
	while (y < data->screen_height)
	{
		if (y <= data->screen_height / 2)
			my_mlx_pixel_put(&data->img, x, y, data->cubfile->colors[CEILING]);
		else
			my_mlx_pixel_put(&data->img, x, y, data->cubfile->colors[FLOOR]);
		if (y >= wall->draw_start && y < wall->draw_end)
		{
			wall->texture_y = (int)wall->texture_pos_y;
			if (wall->texture_y >= ray.tex->height)
				wall->texture_y = ray.tex->height - 1;
			wall->texture_pos_y += wall->step;
			color = get_color_pix(*ray.tex, wall->texture_x, wall->texture_y);
			my_mlx_pixel_put(&data->img, x, y, color);
		}
		y++;
	}
}

void
	draw_wall(t_data *data)
{
	int		x;
	t_ray	ray;
	t_wall	wall;

	x = 0;
	while (x < data->screen_width)
	{
		init_ray(data, &ray, x);
		raycast(data, &ray);
		cal_screen_info(data, ray, &wall);
		draw_stripe(data, ray, &wall, x);
		x++;
	}
}
