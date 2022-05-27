/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 10:13:19 by kfumiya           #+#    #+#             */
/*   Updated: 2022/05/27 10:28:04 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	init_player_dir(t_player *player, char dir)
{
	if (dir == 'N' || dir == 'S')
	{
		player->dir.x = 0;
		player->dir.y = -1;
		player->plane.x = 1 * tan(deg_rad(66 / 2));
		if (dir == 'S')
		{
			player->dir.y = 1;
			player->plane.x = -1 * tan(deg_rad(66 / 2));
		}
		player->plane.y = 0;
	}
	if (dir == 'W' || dir == 'E')
	{
		player->dir.x = -1;
		player->dir.y = 0;
		player->plane.x = 0;
		player->plane.y = -1 * tan(deg_rad(66 / 2));
		if (dir == 'E')
		{
			player->dir.x = 1;
			player->plane.y = 1 * tan(deg_rad(66 / 2));
		}
	}
}

void
	init_player(t_player *player, double x, double y, char dir)
{
	player->pos.x = x;
	player->pos.y = y;
	init_player_dir(player, dir);
	player->is_moving = 0;
	player->is_sidling = 0;
	player->is_rotating = 0;
}
