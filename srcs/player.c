/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 09:47:58 by kfumiya           #+#    #+#             */
/*   Updated: 2022/06/15 13:42:12 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	move_player(t_data *data)
{
	double	new_x;
	double	new_y;

	if (data->player.is_moving)
	{
		new_x = data->player.pos.x + data->player.is_moving \
			* data->player.dir.x * MOVE_P;
		if (new_x < 0)
			new_x = 0;
		if (data->cubfile->map[(int)data->player.pos.y][(int)new_x] != '1')
			data->player.pos.x = new_x;
		new_y = data->player.pos.y + data->player.is_moving \
			* data->player.dir.y * MOVE_P;
		if (new_y < 0)
			new_y = 0;
		if (data->cubfile->map[(int)new_y][(int)data->player.pos.x] != '1')
			data->player.pos.y = new_y;
	}
}

static void
	rotate_player(t_data *data)
{
	double	rot_speed;
	double	rotate_rad;

	rotate_rad = M_PI / 300;
	if (data->player.is_rotating)
	{
		rot_speed = data->player.is_rotating * rotate_rad;
		vec_rotate(&data->player.dir, rot_speed);
		vec_rotate(&data->player.plane, rot_speed);
	}
}

static void
	slide_player(t_data *data)
{
	double	new_x;
	double	new_y;
	t_vec2	perp;

	if (data->player.is_sidling)
	{
		perp = data->player.dir;
		vec_rotate(&perp, M_PI / 2);
		new_x = data->player.pos.x + data->player.is_sidling \
			* perp.x * MOVE_P;
		if (new_x < 0)
			new_x = 0;
		if (data->cubfile->map[(int)data->player.pos.y][(int)new_x] != '1')
			data->player.pos.x = new_x;
		new_y = data->player.pos.y + data->player.is_sidling \
			* perp.y * MOVE_P;
		if (new_y < 0)
			new_y = 0;
		if (data->cubfile->map[(int)new_y][(int)data->player.pos.x] != '1')
			data->player.pos.y = new_y;
	}
}

void
	update_player(t_data *data)
{
	move_player(data);
	slide_player(data);
	rotate_player(data);
}
