/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 21:25:10 by kfumiya           #+#    #+#             */
/*   Updated: 2021/06/06 06:56:20 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_sprite
	*add_sorted_sprite(t_sprite **sorted, t_sprite *sprite)
{
	t_sprite	*first;
	t_sprite	*prev;

	if (!*sorted)
		return ((*sorted = sprite));
	first = *sorted;
	prev = NULL;
	while (*sorted && sprite->distance < (*sorted)->distance)
	{
		prev = *sorted;
		*sorted = (*sorted)->sorted;
	}
	if (!prev)
	{
		sprite->sorted = *sorted;
		*sorted = sprite;
	}
	else
	{
		sprite->sorted = prev->sorted;
		prev->sorted = sprite;
		*sorted = first;
	}
	return (sprite);
}

t_sprite
	*sort_sprites(t_game *game, t_sprite *sprites)
{
	t_sprite	sorted;
	t_pos		p;

	sorted = NULL;
	copy_pos(&p, &game->camera.pos);
	while (sprites)
	{
		sprites->distance =
			fabs(((p.x - sprites->pos.x) * (p.x - sprites->pos.x)
				+ (p.y - sprites->pos.y) * (p.y - sprites->pos.y)));
		sprites->sorted = NULL;
		add_sorted_sprite(&sorted, sprites);
		sprites = sprites->next;
	}
}

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
