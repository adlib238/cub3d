/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:31:18 by kfumiya           #+#    #+#             */
/*   Updated: 2022/05/24 13:26:28 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	read_image(t_game *game, t_img *img, char *filepath)
{
	img->img = mlx_xpm_file_to_image(game->mlx, filepath,
		&img->width, &img->height);
	if (img->img == NULL)
		return (ERROR);
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
		&img->line_length, &img->endian);
	if (img->addr == NULL)
		return (ERROR);
	return (0);
}
