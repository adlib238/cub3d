/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 21:03:32 by kfumiya           #+#    #+#             */
/*   Updated: 2021/06/06 06:59:41 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void
// 	draw_sprites(t_game *game)
// {
// 	t_sprite		*sorted;
// 	double			inv_det;
// 	t_sprite_draw	spr;

// 	inv_det = 1 / ((game->camera.plane.x * game->camera.dir.y)
// 				- (game->camera.plane.y * game->camera.dir.x));
// 	sorted = sort_sprites(game, game->sprites);
// 	while (sorted)
// 	{
// 		if (sorted->distance > 1)
// 		{
// 			init_draw_sprite(game, sorted, inv_det, &spr);
// 			draw_sprite(game, sorted, &spr, sorted->tex);
// 		}
// 		sorted = sorted->sorted;
// 	}
// }

void
	clear_sprites(t_sprite **sprites)
{
	t_sprite	*tmp;

	while (*sprites)
	{
		tmp = (*sprites)->next;
		free(*sprites);
		*sprites = tmp;
	}
	*sprites = NULL;
}
