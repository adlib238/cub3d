/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:09:22 by kfumiya           #+#    #+#             */
/*   Updated: 2022/05/29 09:40:21 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	rotate_player(t_game *game)
{
	double	rot_speed;
	
	if (game->player.is_rotating)
	{
		rot_speed = game->player.is_rotating * ROTATE_RAD;
		vec_rotate(&game->player.dir, rot_speed);
		vec_rotate(&game->player.plane, rot_speed);
	}
}

static void
	move_player(t_game *game)
{
	double	new_x;
	double	new_y;

	if (game->player.is_moving)
	{
		new_x = game->player.pos.x + game->player.is_moving \
			* game->player.dir.x * MOVE_PX;
		if (new_x < 0)
			new_x = 0;
		if (game->map[(int)(game->player.pos.y)][(int)new_x] != '1')
			game->player.pos.x = new_x;
		new_y = game->player.pos.y + game->player.is_moving \
			* game->player.dir.y * MOVE_PX;
		if (new_y < 0)
			new_y = 0;
		if (game->map[(int)(new_y)][(int)game->player.pos.x] != '1')
			game->player.pos.y = new_y;
	}
}

static void
	slide_player(t_game *game)
{
	double	new_x;
	double	new_y;
	t_vec2	perpendicular;

	if (game->player.is_sidling)
	{
		perpendicular = game->player.dir;
		vec_rotate(&perpendicular, M_PI / 2);
		new_x = game->player.pos.x + game->player.is_sidling \
			* perpendicular.x * MOVE_PX;
		if (new_x < 0)
			new_x = 0;
		if (game->map[(int)(game->player.pos.y)][(int)new_x] != '1')
			game->player.pos.x = new_x;
		new_y = game->player.pos.y + game->player.is_sidling \
			* perpendicular.y * MOVE_PX;
		if (new_y < 0)
			new_y = 0;
		if (game->map[(int)new_y][(int)(game->player.pos.x)] != '1')
			game->player.pos.y = new_x;	
	}
}

void
	update_player(t_game *game)
{
	move_player(game);
	slide_player(game);
	rotate_player(game);
}