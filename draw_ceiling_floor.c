/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ceiling_floor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 19:33:56 by kfumiya           #+#    #+#             */
/*   Updated: 2021/05/07 22:24:53 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	init_draw_ceiling_floor(t_ray *ray)
{
	if (ray->side == 0 && ray->ray_dir.x > 0)
		set_pos(&ray->floor_wall,
				ray->map_pos.x, ray->map_pos.y + ray->wall_x);
	else if (ray->side == 0 && ray->ray_dir.x < 0)
		set_pos(&ray->floor_wall,
				ray->map_pos.x + 1, ray->map_pos.y + ray->wall_x);
	else if (ray->side && ray->ray_dir.y > 0)
		set_pos(&ray->floor_wall,
				ray->map_pos.x + ray->wall_x, ray->map_pos.y);
	else if (ray->side && ray->ray_dir.y < 0)
		set_pos(&ray->floor_wall,
				ray->map_pos.x + ray->wall_x, ray->map_pos.y + 1);
}

void
	draw_ceiling_floor(t_game *game, t_ray *ray)
{
	int		i;
	t_pos	pixel;
	double	weight;

	init_draw_ceiling_floor(ray);
	pixel.x = ray->column;
	i = (game->window.size.y / 2) + (ray->height / 2);
	while (i < game->window.size.y)
	{
		ray->row = (int)i;
		weight = game->sf_dist[i] / ray->distance;
		set_pos(&ray->c_floor,
			weight * ray->floor_wall.x + (1 - weight) * game->camera.pos.x,
			weight * ray->floor_wall.y + (1 - weight) * game->camera.pos.y);
		pixel.y = i;
		draw_pixel(&game->window, &pixel, game->config.c[TEX_CEILING]);
		pixel.y = game->window.size.y - i++;
		draw_pixel(&game->window, &pixel, game->config.c[TEX_FLOOR]);
	}
}
