/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 11:45:34 by kfumiya           #+#    #+#             */
/*   Updated: 2022/05/23 15:17:28 by kfumiya          ###   ########.fr       */
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
	// char *line;

	printf("%d\n", fd);
	printf("%d\n", game->map_col);

	status = 0;
	// while (status >= 0)
	// {
	// 	line = NULL;
		
	// }
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
	// print map
	// printf("----------------------INPUT MAP---------------------\n");
	// for (int i = 0; i < game->map_row; i++)
	// 	printf("%s\n", game->map[i]);
	return (0);
}