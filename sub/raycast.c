/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 05:41:01 by kfumiya           #+#    #+#             */
/*   Updated: 2021/05/08 02:16:18 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	wall_direction(t_ray *ray)
{
	if (ray->side)
		return ((ray->ray_dir.y < 0) ? (TEX_NORTH) : (TEX_SOUTH));
	return ((ray->ray_dir.x < 0) ? (TEX_WEST) : (TEX_EAST));
}

double
	ray_distance(t_game *game, t_ray *ray)
{
	double	pos;

	if (!ray->side)
	{
		pos = (ray->map_pos.x - game->camera.pos.x + (1 - ray->step.x) / 2);
			return (fabs(pos / ray->ray_dir.x));
	}
	pos = (ray->map_pos.y - game->camera.pos.y + (1 - ray->step.y) / 2);
		return(fabs(pos / ray->ray_dir.y));
}

static void
	wallhit(t_game *game, t_ray *ray)
{
	int hit;
	int next_side;

	hit = 0;
	while (!hit)
	{
		next_side = (ray->side_dist.x < ray->side_dist.y);
		ray->side_dist.x += ((next_side) ? ray->delta_dist.x : 0);
		ray->map_pos.x += ((next_side) ? ray->step.x : 0);
		ray->side_dist.y += ((!next_side) ? ray->delta_dist.y : 0);
		ray->map_pos.y += ((!next_side) ? ray->step.y : 0);
		ray->side = !next_side;
		// if (!IN_MAP(ray->map_pos, game->config))
		// {
		// 	ray->map_pos.x -= ((!ray->side) ? ray->step.x : 0);
		// 	ray->map_pos.y -= ((ray->side) ? ray->step.y : 0);
		// 	hit = 1;
		// }
		if (MAP(ray->map_pos, game->config) == 1)
			hit = 1;
	}
}

static void
	init_ray(t_ray *ray, t_camera *c, int column, double camera_x)
{
	ray->column = column;
	set_pos(&ray->map_pos, (int)c->pos.x, (int)c->pos.y);
	set_pos(&ray->ray_dir, c->dir.x + c->plane.x * camera_x,
			c->dir.y + c->plane.y * camera_x);
	set_pos(&ray->delta_dist,
			fabs(1 / ray->ray_dir.x), fabs(1 / ray->ray_dir.y));
	if (ray->ray_dir.x < 0)
	{
		set_pos(&ray->step, -1, (ray->ray_dir.y < 0) ? -1 : 1);
		ray->side_dist.x =
			(ray->ray_pos.x - ray->map_pos.x) * ray->delta_dist.x;
	}
	else
	{
		set_pos(&ray->step, 1, (ray->ray_dir.y < 0) ? -1 : 1);
		ray->side_dist.x =
			(ray->map_pos.x + 1 - ray->ray_pos.x) * ray->delta_dist.x;
	}
	if (ray->ray_dir.y < 0)
		ray->side_dist.y =
			(ray->ray_pos.y - ray->map_pos.y) * ray->delta_dist.y;
	else
		ray->side_dist.y =
			(ray->map_pos.y + 1 - ray->ray_pos.y) * ray->delta_dist.y;
}

void
	raycast(t_game *game, t_ray *ray, int column)
{
	copy_pos(&ray->ray_pos, &game->camera.pos);
	init_ray(ray, &game->camera, column, game->camera_x[column]);
	wallhit(game, ray);
	ray->distance = ray_distance(game, ray);
	ray->direction = wall_direction(ray);
}
