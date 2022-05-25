/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 10:33:38 by kfumiya           #+#    #+#             */
/*   Updated: 2022/05/25 09:44:49 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool
	str_isvalid_color_set(char *str)
{
	if (!str_isvalid_set(str, ft_isdigit))
		return (false);
	if (str[0] == '0' && str[1])
		return (false);
	return (true);
}

static bool
	isvalid_color(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (false);
	return (true);
}

static int
	read_color(char *rgb, uint32_t *color)
{
	char	**strs;
	int		c[3];

	strs = ft_split(rgb, ',');
	if (!strs && strs_size(strs) != 3)
		return (ERROR);
	if (!str_isvalid_color_set(strs[0])
		|| !str_isvalid_color_set(strs[1])
		|| !str_isvalid_color_set(strs[2]))
	{
		instant_free((void **)strs);
		return (ERROR);
	}
	c[0] = ft_atoi(strs[0]);
	c[1] = ft_atoi(strs[1]);
	c[2] = ft_atoi(strs[2]);
	if (!isvalid_color(c[0], c[1], c[2]))
	{
		instant_free((void **)strs);
		return (ERROR);
	}
	*color = c[0] << 16 | c[1] << 8 | c[0];
	instant_free((void **)strs);
	return (0);
}

static bool
	check_color_set(t_game *game, char c)
{
	if (c == 'C' && game->sky_color == UINT32_MAX)
		return (false);
	if (c == 'F' && game->ground_color == UINT32_MAX)
		return (false);
	return (true);
}

int
	set_color(t_game *game, char c, char *rgb)
{
	uint32_t	color;

	color = 0;
	if (read_color(rgb, &color) == ERROR)
		return (return_error_msg("color is invalid"));
	if (check_color_set(game, c))
		return (return_error_msg("The color is already set"));
	if (c == 'C')
		game->sky_color = color;
	else if (c == 'F')
		game->ground_color = color;
	else
		return (return_error_msg("invalid color identifier"));
	return (0);
}
