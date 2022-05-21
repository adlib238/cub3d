/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 17:08:49 by kfumiya           #+#    #+#             */
/*   Updated: 2021/06/05 21:51:47 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	check_valid(t_config *config, t_str *map_buffer)
{
	int	i;

	while (map_buffer)
	{
		i = 0;
		while (map_buffer->content[i])
		{
			if (!ft_in_set(map_buffer->content[i], VALID_MAP_CHARACTERS))
				return (0);
			if (ft_in_set(map_buffer->content[i], DIRECTIONS))
				config->pl_pos += 1;
			i++;
		}
		map_buffer = map_buffer->next;
	}
	return (1);
}

void
	check_map(t_config *config, int x, int y, int *code)
{
	int	**map;

	map = config->map;
	if (map[x][y] == 1 || map[x][y] == 3 || map[x][y] == 4)
		return ;
	if (x == 0 || y == 0 || x == config->rows)
	{
		*code = 1;
		return ;
	}
	if (map[x][y] == -1 || map[x][y] == 8)
	{
		*code = 1;
		return ;
	}
	if (map[x][y] == 0)
		map[x][y] = 3;
	if (map[x][y] == 2)
		map[x][y] = 4;
	check_map(config, x + 1, y, code);
	check_map(config, x, y + 1, code);
	check_map(config, x - 1, y, code);
	check_map(config, x, y - 1, code);
}
