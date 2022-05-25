/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:35:07 by kfumiya           #+#    #+#             */
/*   Updated: 2022/05/25 10:53:50 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool
	check_config_set(t_game *game)
{
	/* 
	if (game->screen_height == -1 || game->screen_width == -1
		|| game->sky_color == UINT32_MAX || game->ground_color == UINT32_MAX
		|| !game->tex_n.img || !game->tex_s.img || !game->tex_w.img
		|| !game->tex_e.img)
 */
	if (game->screen_height == -1 || game->screen_width == -1
		|| game->sky_color == UINT32_MAX || game->ground_color == UINT32_MAX)
		return (false);
	return (true);
}

int
	read_map(t_game *game, char *line)
{
	if (!check_config_set(game))
		return (return_error_msg("Insufficient settings for map components"));
	if (!line || ft_strlen(line) >= MAX_MAP_W || ft_strlen(line) >= MAX_MAP_H)
	{
		put_err_msg("map is size over");
		return (ERROR);
	}
	game->map[game->map_row] = ft_calloc(MAX_MAP_W, sizeof(char));
	ft_strlcpy(game->map[game->map_row], line, ft_strlen(line) + 1);
	if (!game->map[game->map_row])
	{
		put_err_msg("memory error");
		return (ERROR);
	}
	game->map_row++;
	game->map_col = MAX((int)ft_strlen(line), game->map_col);
	return (0);
}
