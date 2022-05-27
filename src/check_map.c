/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:02:40 by kfumiya           #+#    #+#             */
/*   Updated: 2022/05/27 09:45:07 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool
	floodfill(t_game *game, bool **fill_map, int i, int j)
{
	bool	is_valid;

	if (i < 0 || i >= game->map_row || j < 0 || j >= game->map_col)
		return (false);
	if (game->map[i][j] == '1' || fill_map[i][j] == true)
		return (true);
	else
		fill_map[i][j] = true;
	is_valid = true;
	is_valid &= floodfill(game, fill_map, i - 1, j);
	is_valid &= floodfill(game, fill_map, i + 1, j);
	is_valid &= floodfill(game, fill_map, i, j - 1);
	is_valid &= floodfill(game, fill_map, i, j + 1);
	return (is_valid);
}

int
	check_map(t_game *game)
{
	int		x;
	int		y;
	int		i;
	bool	**fill_map;

	x = game->player.pos.x;
	y = game->player.pos.y;
	fill_map = ft_calloc(game->map_row + 1, sizeof(bool *));
	i = 0;
	while (i < game->map_row)
	{
		fill_map[i] = ft_calloc(game->map_col, sizeof(bool));
		if (!fill_map[i])
		{
			return (return_error_msg("malloc error"));
		}
		i++;
	}
	return (floodfill(game, fill_map, y, x));
}
