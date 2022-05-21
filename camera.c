/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 17:39:24 by kfumiya           #+#    #+#             */
/*   Updated: 2021/05/05 20:37:38 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	set_start_pos(t_config *config, t_camera *camera)
{
	camera->pos.x = config->pl_x + 0.5;
	camera->pos.y = config->pl_y + 0.5;
}

void
	set_start_angle(t_config *config, t_camera *camera)
{
	if (config->pl_dir == 'N')
	{
		set_pos(&camera->dir, 0, -1);
		set_pos(&camera->plane, config->fov, 0);
	}
	else if (config->pl_dir == 'E')
	{
		set_pos(&camera->dir, 1, 0);
		set_pos(&camera->plane, 0, config->fov);
	}
	else if (config->pl_dir == 'S')
	{
		set_pos(&camera->dir, 0, 1);
		set_pos(&camera->plane, -config->fov, 0);
	}
	else if (config->pl_dir == 'W')
	{
		set_pos(&camera->dir, -1, 0);
		set_pos(&camera->plane, 0, -config->fov);
	}
	set_pos(&camera->x_dir, camera->dir.y, -camera->dir.x);
}

int
	move_camera(t_game *game, int direction)
{
	t_camera	*c;
	t_pos		new_pos;

	c = &game->camera;
	copy_pos(&new_pos, &c->pos);
	new_pos.x += (((direction) ? -1 : 1) * (c->dir.x * .11));
	if (IN_MAP(new_pos, game->config)
		&& MAP(new_pos, game->config) != '1'
		&& MAP(new_pos, game->config) != '2')
		copy_pos(&c->pos, &new_pos);
	copy_pos(&new_pos, &c->pos);
	new_pos.y += (((direction) ? -1 : 1) * (c->dir.y * .11));
	if (IN_MAP(new_pos, game->config)
		&& MAP(new_pos, game->config) != '1'
		&& MAP(new_pos, game->config) != '2')
		copy_pos(&c->pos, &new_pos);
	return (1);
}

int
	move_perp_camera(t_game *game, int direction)
{
	t_camera	*c;
	t_pos		new_pos;

	c = &game->camera;
	copy_pos(&new_pos, &c->pos);
	new_pos.x += (((direction) ? -1 : 1) * (c->x_dir.x * .11) + 0.00001);
	if (IN_MAP(new_pos, game->config)
		&& MAP(new_pos, game->config) != '1'
		&& MAP(new_pos, game->config) != '2')
		copy_pos(&c->pos, &new_pos);
	copy_pos(&new_pos, &c->pos);
	new_pos.y += (((direction) ? -1 : 1) * (c->x_dir.y * .11) + 0.00001);
	if (IN_MAP(new_pos, game->config)
		&& MAP(new_pos, game->config) != '1'
		&& MAP(new_pos, game->config) != '2')
		copy_pos(&c->pos, &new_pos);
	return (1);
}

int
	rotate_camera(t_game *game, int dir)
{
	t_camera	*c;
	t_pos		old;

	c = &game->camera;
	copy_pos(&old, &c->dir);
	c->dir.x = (c->dir.x * game->cos[dir]) - (c->dir.y * game->sin[dir]);
	c->dir.y = (old.x * game->sin[dir]) + (c->dir.y * game->cos[dir]);
	copy_pos(&old, &c->plane);
	c->plane.x = (c->plane.x * game->cos[dir]) - (c->plane.y * game->sin[dir]);
	c->plane.y = (old.x * game->sin[dir]) + (c->plane.y * game->cos[dir]);
	copy_pos(&old, &c->x_dir);
	c->x_dir.x = (c->x_dir.x * game->cos[dir]) - (c->x_dir.y * game->sin[dir]);
	c->x_dir.y = (old.x * game->sin[dir]) + (c->x_dir.y * game->cos[dir]);
	return (1);
}