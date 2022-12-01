/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:54:01 by mmasubuc          #+#    #+#             */
/*   Updated: 2022/06/15 18:36:55 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"

void	parse_map(t_data *data, char *file)
{
	int		fd;
	char	**map_dup;

	data->cubfile->map
		= (char **)malloc(sizeof(char *) * (data->cubfile->map_row + 1));
	if (!data->cubfile->map)
		exit_program(MALLOC_FAIL, data, ALL_DIRECTION);
	fd = open(file, O_RDONLY);
	read_through_type_info(fd, data);
	if (!read_map(data, fd))
		exit_program(INVALID_MAP, data, ALL_DIRECTION);
	if (close(fd) == ERROR)
		exit_program(CLOSE_FAIL, data, ALL_DIRECTION);
	map_dup = make_copy_map(data);
	if (!map_dup)
		exit_program(MALLOC_FAIL, data, ALL_DIRECTION);
	if (!is_closed_by_wall(
			map_dup, data->player.pos.y, data->player.pos.x, data))
		exit_program(INVALID_MAP, data, ALL_DIRECTION);
	free_2d_array(map_dup);
}

void	read_through_type_info(int fd, t_data *data)
{
	char	*line;
	size_t	i;

	i = 0;
	while (i < NB_TYPE)
	{
		get_next_line(fd, &line, data, ALL_DIRECTION);
		if (ft_strlen(line) != 0)
			i++;
		free_buf((void **)&line);
	}
}

bool	read_map(t_data *data, int fd)
{
	size_t	i;

	i = 0;
	while (i < data->cubfile->map_row)
	{
		get_next_line(fd, &data->cubfile->map[i], data, ALL_DIRECTION);
		if (ft_strlen(data->cubfile->map[i]) == 0)
		{
			free_buf((void **)&data->cubfile->map[i]);
			continue ;
		}
		if (!get_ppos(data, data->cubfile->map[i], i))
			return (false);
		i++;
	}
	data->cubfile->map[i] = NULL;
	return (true);
}

bool	get_ppos(t_data *data, char *line, int row)
{
	int	col;
	int	llen;

	col = 0;
	llen = ft_strlen(line);
	if (llen == 0)
		return (false);
	while (line[col] != '\0')
	{
		if (ft_strchr("NSWE", line[col]))
		{
			if (data->player.direction != ALL_DIRECTION)
				return (false);
			data->player.pos.x = col + 0.5;
			data->player.pos.y = row + 0.5;
			data->player.direction = line[col];
		}
		else if (!ft_strchr(" 01", line[col]))
			return (false);
		col++;
	}
	return (true);
}

bool	is_closed_by_wall(char **map, int row, int col, t_data *data)
{
	if (row < 0 || row >= (int)data->cubfile->map_row
		|| col < 0 || col >= (int)data->cubfile->map_col)
		return (false);
	if (map[row][col] == ' ' || map[row][col] == '\0')
		return (false);
	if (map[row][col] == '1' || map[row][col] == 'X')
		return (true);
	map[row][col] = 'X';
	return (is_closed_by_wall(map, row + 1, col, data)
		&& is_closed_by_wall(map, row - 1, col, data)
		&& is_closed_by_wall(map, row, col + 1, data)
		&& is_closed_by_wall(map, row, col - 1, data));
}
