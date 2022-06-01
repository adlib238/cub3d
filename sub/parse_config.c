/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 22:08:16 by kfumiya           #+#    #+#             */
/*   Updated: 2021/06/06 00:24:26 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	init_config(t_config *config)
{
	int	i;

	config->requested_width = 848;
	config->requested_height = 480;
	i = 0;
	while (i < TEXTURES)
	{
		config->tex_path[i] = NULL;
		config->c[i] = 0;
		i++;
	}
	config->map = NULL;
	config->rows = 0;
	config->columns = 0;
	i = 0;
	while (i < C_LAST)
		config->set[i++] = 0;
	config->pl_x = 0;
	config->pl_y = 0;
	config->pl_pos = 0;
	// config->rotate_speed = .11;
	// config->move_speed = .11;
	// config->fov = .66;
}

static int
	config_key(char const *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == 'R' && line[i + 1] == ' ')
		return (C_R);
	else if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		return (C_NO);
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		return (C_SO);
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		return (C_WE);
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		return (C_EA);
	else if (line[i] == 'S' && line[i + 1] == ' ')
		return (C_S);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		return (C_F);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		return (C_C);
	return (C_MAP);
}

int
	parse_line(t_config *config, char const *line, t_str **map_buffer)
{
	static int	content_after = 0;
	static int	empty_map = 0;
	int			key;
	int			length;

	length = ft_strlen(line);
	if (length == 0 && config->set[C_MAP])
		empty_map = 1;
	if (empty_map && content_after)
		return (0);
	if (length == 0)
		return (1);
	key = config_key(line);
	if (key != C_MAP && config->set[C_MAP])//config->set[key] || 
		return (0);
	if (key == C_R)
		return (parse_dimensions(config, key, line));
	else if (key >= C_NO && key <= C_S)
		return (parse_textures(config, key, line));
	else if (key == C_F || key == C_C)
		return (parse_color(config, key, line));
	config->set[key] = 1;
	if (empty_map)
		content_after = 1;
	return (!!str_add_back(map_buffer, ft_strdup(line)));
}

int
	parse_config(t_game *game, char *file_path)
{
	int fd;
	char *line;
	t_str *map_buffer;
	int r;

	if (!ft_endwith(file_path, ".cub"))
		put_error("Error:\nfilepath not .cub\n", game);
	if ((fd = open(file_path, O_RDONLY)) < 0)
		put_error("Error:\ncub file not found\n", game);
	map_buffer = NULL;
	r = 1;
	while (get_next_line(fd, &line))
	{
		r = (r && parse_line(&game->config, line, &map_buffer));
		free(line);
	}
	if (r && ft_strlen(line) > 0)
		r = !!str_add_back(&map_buffer, ft_strdup(line));
	free(line);
	close(fd);
	if (!r || !parse_map(&game->config, map_buffer, game))
		return (str_clear(&map_buffer));
	str_clear(&map_buffer);
	return (1);
}
