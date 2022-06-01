/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 20:21:32 by kfumiya           #+#    #+#             */
/*   Updated: 2021/05/08 22:05:15 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	init_draw_wall(t_tex *tex, t_ray *ray, t_pos *p_tex)
{
	if (ray->side)
		ray->wall_x = ray->ray_pos.x
			+ ((ray->map_pos.y - ray->ray_pos.y
				+ (1 - ray->step.y) / 2) / ray->ray_dir.y)
			* ray->ray_dir.x;
	else
		ray->wall_x = ray->ray_pos.y
			+ ((ray->map_pos.x - ray->ray_pos.x
				+ (1 - ray->step.x) / 2) / ray->ray_dir.x)
			* ray->ray_dir.y;
	ray->wall_x -= floor(ray->wall_x);
	p_tex->x = (int)(ray->wall_x * tex->width);
	if (ray->side == 0 && ray->ray_dir.x > 0)
		p_tex->x = tex->width - p_tex->x - 1;
	else if (ray->side == 1 && ray->ray_dir.y < 0)
		p_tex->x = tex->width - p_tex->x - 1;
}


static void	
	verLine(t_game *game, t_ray *ray, int y1, int y2, int color)
{
	int	y;

	y = y1;
	while (y <= y2)
	{
		mlx_pixel_put(game->window.ptr, game->window.win, ray->column, y, color);
		y++;
	}
}

void
	draw_wall(t_game *game, t_ray *ray)
{
	t_tex	*tex;
	t_pos	pixel;
	t_pos	p_tex;
	int		i;
	int		j;

	tex = &game->tex[ray->direction];
	set_pos(&pixel, ray->column,
			MAX(0, (game->window.size.y / 2) - (ray->height / 2)));
	if (!tex->tex)
	{
		draw_vertical_line(&game->window, &pixel, ray->height,
			distance_shade(game->options,
			game->config.c[ray->direction], ray->distance));
		return ;
	}
	init_draw_wall(tex, ray, &p_tex);
	i = 0;
	j = MAX(0, (game->window.size.y / 2) - (ray->height / 2));
	while (0 < ray->height && (pixel.y = j++) < game->window.size.y)
	{
		p_tex.y = (int)((pixel.y * 2 - game->window.size.y + ray->height)
					* ((tex->height / 2) / ray->height));
		draw_pixel(&game->window, &pixel, distance_shade(game->options,
			get_tex_color(tex, &p_tex), ray->distance));
		i++;
	}
}
