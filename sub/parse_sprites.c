/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 05:39:46 by kfumiya           #+#    #+#             */
/*   Updated: 2021/06/06 00:59:41 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_sprite
	*add_front_sprite(t_sprite **sprites, double distance, t_pos *pos,
		char **tex_path)
{
	t_sprite	*new;

	if (!(new = (t_sprite *)malloc(sizeof(*new))))
		return (NULL);
	copy_pos(&new->pos, pos);
	new->distance = distance;
	new->next = *sprites;
	new->tex_path = tex_path[TEX_SPRITE];
	*sprites = new;
	return (new);
}

static int
	count_sprites(t_config *config)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (i < config->rows)
	{
		j = 0;
		while (j < config->columns)
		{
			if (config->map[i][j] == 4)
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

int
	get_sprites(t_game *game)
{
	int			x;
	int			y;
	t_pos		pos;

	game->sp_count = count_sprites(&game->config);
	x = 0;
	while (x < game->config.rows)
	{
		y = 0;
		while (y < game->config.columns)
		{
			if (game->config.map[x][y] == 4)
			{
				set_pos(&pos, x + 1, y + 1);
				if (!add_front_sprite(&game->sprites, 0, &pos,
						game->config.tex_path))
					return (0);
			}
			y++;
		}
		x++;
	}
	return (1);
}
