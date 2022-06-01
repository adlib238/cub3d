/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 11:45:34 by kfumiya           #+#    #+#             */
/*   Updated: 2022/05/26 15:11:40 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool
	is_valid_filepath(char *path)
{
	size_t	len;

	len = ft_strlen(path);
	if (len < 5 || path[len - 5] == '/' \
			|| ft_strncmp(path + len - 4, ".cub", 4))
		return (false);
	return (true);
}

static int
	read_config(t_game *game, int fd)
{
	int		status;
	char	*line;
	char	**elems;

	status = 0;
	while (status >= 0)
	{
		line = readline(fd);
		if (!line)
			break ;
		// printf("line: %s\n", line);
		elems = ft_split(line, ' ');
		if (!elems)
			status = ERROR;
		if (status >= 0 && elems[0] && !ft_strcmp(elems[0], "R"))
			status = set_resolution(game, elems[1], elems[2]);
		else if (status >= 0 && elems[0] && ft_in_set(elems[0][0], "FC"))
			status = set_color(game, elems[0][0], elems[1]);
		else if (status >= 0 && elems[0] && is_texture(elems[0]))
			status = read_texture(game, elems[0], elems[1]);
		else if (status >= 0 && elems[0])
			status = read_map(game, line);
		set_free((void **)&line, NULL);
		instant_free((void **)elems);
	}
	set_free((void **)&line, NULL);
	return (status);
}

static int
	get_player_pos(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < game->map_row)
	{
		while (++j < game->map_col)
		{
			if (game->map[i][j] == '\0')
				continue ;
			if (!ft_in_set(game->map[i][j], " 01NSWE"))
				return (return_error_msg("Map has invalid characters"));
			if (ft_in_set(game->map[i][j], "NSWE"))
			{
				if (game->player.pos.x != ERROR && game->player.pos.y != ERROR)
					return (return_error_msg("Player must be alone"));
				init_player(&game->player, j + 0.5, i + 0.5, game->map[i][j]);
			}
		}
	}
	if (game->player.pos.x == ERROR && game->player.pos.y == ERROR)
		return (return_error_msg("Player is not set"));
	return (0);
}

int
	read_cub(t_game *game, char *path)
{
	int	fd;
	int	status;

	if (!is_valid_filepath(path))
		return (return_error_msg("File specifier must be .cub"));
	fd = open(path, O_RDONLY);
	if (fd == ERROR)
		return (return_error_msg("The file could not be opened"));
	status = read_config(game, fd);
	if (status == ERROR || get_player_pos(game) || check_map(game))
		return (return_error_msg("cub file settings are incorrect"));
	print_config(game);
	return (0);
}
