/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 03:46:28 by kfumiya           #+#    #+#             */
/*   Updated: 2021/06/05 23:08:22 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	player_set(t_config *config, int i, int j, char dir)
{
	config->pl_x = i + 1;
	config->pl_y = j + 1;
	config->pl_dir = dir;
	config->map[i][j] = 0;
}

void
	modify_map(t_config *config, t_str *map_buffer)
{
	int	i;
	int	j;

	i = 0;
	while (map_buffer)
	{
		j = 0;
		while (map_buffer->content[j])
		{
			if (map_buffer->content[j] == ' ')
				config->map[i][j] = 8;
			else if (ft_in_set(map_buffer->content[j], DIRECTIONS))
				player_set(config, i, j, map_buffer->content[j]);
			else
				config->map[i][j] = map_buffer->content[j] - '0';
			j++;
		}
		i++;
		map_buffer = map_buffer->next;
	}
}

int
	init_map(t_config *config)
{
	int	i;
	int	j;

	i = 0;
	if (!(config->map = (int **)malloc(sizeof(int *) * (config->rows))))
		return (0);
	while (i < config->rows)
	{
		j = 0;
		if (!(config->map[i] = malloc(sizeof(int) * (config->columns))))
			return (0);
		while (j < config->columns)
		{
			config->map[i][j] = -1;
			j++;
		}
		i++;
	}
	return (1);
}

int
	get_max_columns(t_str *map_buffer)
{
	int	col;
	int end;

	col = 0;
	while (map_buffer)
	{
		end = ft_strlen(map_buffer->content);
		while (map_buffer->content[end - 1] == ' ')
			end--;
		if (col < end)
			col = end;
		map_buffer = map_buffer->next;
	}
	return (col);
}

int
	parse_map(t_config *config, t_str *map_buffer, t_game *game)
{
	int	code;

	code = 0;
	if ((config->rows = str_length(map_buffer) + 1) <= 2
		|| (config->columns = get_max_columns(map_buffer) + 1) <= 2
		|| !check_valid(config, map_buffer))
		return (0);
	if (config->pl_pos != 1)
		return (out_error("Error:\nset player error.\n"));
	if (!init_map(config))
		return (0);
	modify_map(config, map_buffer);
	check_map(config, config->pl_x, config->pl_y, &code);
	if (code)
		return (out_error("Error:\nmap error.\n"));
	if (!get_sprites(game))
		return (out_error("Error:\nfaild to malloc sprite.\n"));
	return (1);
}
