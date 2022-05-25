/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 11:45:34 by kfumiya           #+#    #+#             */
/*   Updated: 2022/05/25 10:58:40 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool
	is_valid_filepath(char *path)
{
	size_t len;

	len = ft_strlen(path);
	if (len < 5 || path[len - 5] == '/' \
			|| ft_strncmp(path + len - 4, ".cub", 4))
		return (false);
	return (true);
}

static int
	read_config(t_game *game, int fd)
{
	int status;
	char *line;
	char **elems;

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

int
	read_cub(t_game *game, char *path)
{
	int	fd;
	int	status;

	if (!is_valid_filepath(path))
		return (return_error_msg("File specifier must be .cub"));
	if ((fd = open(path, O_RDONLY)) == -1)
		return (return_error_msg("The file could not be opened"));
	status = read_config(game, fd);
	if (status == ERROR)
		return (return_error_msg("cub file settings are incorrect"));
	print_config(game);
	return (0);
}