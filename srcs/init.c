/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:29:30 by mmasubuc          #+#    #+#             */
/*   Updated: 2022/06/17 10:00:02 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_data *data)
{
	int	i;

	i = 0;
	init_mlx(data);
	data->player.direction = ALL_DIRECTION;
	data->player.pos.x = -1;
	data->player.pos.y = -1;
	data->cubfile = (t_cubfile *)malloc(sizeof(t_cubfile));
	if (!data->cubfile)
		exit_program(MALLOC_FAIL, data, 0);
	while (i < ALL_DIRECTION)
		data->cubfile->textures[i++] = NULL;
	data->cubfile->colors[FLOOR] = RGB_MAX + 1;
	data->cubfile->colors[CEILING] = RGB_MAX + 1;
	data->cubfile->map_row = 0;
	data->cubfile->map_col = 0;
	data->cubfile->map = NULL;
}

void	init_mlx(t_data *data)
{
	data->win = NULL;
	data->mlx = mlx_init();
	if (!data->mlx)
		exit_program(MLX_INIT_FAIL, data, 0);
	data->screen_width = 850;
	data->screen_height = 500;
}
