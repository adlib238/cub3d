/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:09:34 by kfumiya           #+#    #+#             */
/*   Updated: 2022/05/25 10:20:14 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool
	is_texture(char *s)
{
	if (!ft_strcmp(s, "NO"))
		return (true);
	else if (!ft_strcmp(s, "SO"))
		return (true);
	else if (!ft_strcmp(s, "WE"))
		return (true);
	else if (!ft_strcmp(s, "EA"))
		return (true);
	return (false);
}

static bool
	check_tex_set(t_game *game, char *s)
{
	if (ft_strcmp(s, "NO") && game->tex_n.img)
		return (true);
	else if (ft_strcmp(s, "SO") && game->tex_s.img)
		return (true);
	else if (ft_strcmp(s, "WE") && game->tex_w.img)
		return (true);
	else if (ft_strcmp(s, "EA") && game->tex_e.img)
		return (true);
	return (false);
}

void samp(t_img *tex)
{
	printf("%p\n", tex);
}

int
	read_texture(t_game *game, char *s, char *path)
{
	t_img	*tex;

	printf("name: %s, path: %s\n", s, path);
	tex = NULL;
	if (check_tex_set(game, s))
		return (return_error_msg("The direction texture is already set"));
	if (ft_strcmp(s, "NO"))
		tex = &game->tex_n;
	else if (ft_strcmp(s, "SO"))
		tex = &game->tex_s;
	else if (ft_strcmp(s, "WE"))
		tex = &game->tex_w;
	else if (ft_strcmp(s, "EA"))
		tex = &game->tex_e;
	samp(tex);
	// if (read_image(game, tex, path) == ERROR)
	// 	return (return_error_msg("Failed to read texture"));
	return (0);
}