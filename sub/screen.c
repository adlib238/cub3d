/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 01:23:53 by kfumiya           #+#    #+#             */
/*   Updated: 2021/06/06 07:43:31 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	update_screen(t_game *game)
{
	//FLOOR CASTING
	floor_cast(game);
	
	// WALL CASTING
	// wall_cast(game);

	//スプライトキャスティング
	//スプライトを遠くから閉じるように並べ替えます
	// sprite_cast(game);

	// t_window	*win;
	// int			i;

	// win = &game->window;	
	// // set_pos(&start, 0, 0);
	// // draw_rectangle(win, &start, &win->size, 0x0);
	// i = 0;
	// while (i < win->size.x)
	// {
	// 	raycast(game, &ray, i);
	// 	// game->depth[i] = ray.distance;
	// 	ray.height = fabs(win->size.y / ray.distance);
	// 	draw_wall(game, &ray);
	// 	// if (ray.height < game->window.size.y)
	// 	// 	draw_ceiling_floor(game, &ray);
	// 	i++;
	// }
	// // if (game->sprites)
	// // 	draw_sprites(game);
}
