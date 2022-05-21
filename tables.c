/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tables.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 08:26:34 by kfumiya           #+#    #+#             */
/*   Updated: 2021/06/06 08:04:46 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void
// 	calculate_camera_x(double width, double *camera_x)
// {
// 	int	i;

// 	i = 0;
// 	while (i < width)
// 	{
// 		camera_x[i] = ((2 * (double)i) / width) - 1;
// 		i++;
// 	}
// }

// static void
// 	calculate_cos_sin(double rotate_speed, double *cos_r, double *sin_r)
// {
// 	cos_r[0] = cos(-rotate_speed);
// 	cos_r[1] = cos(rotate_speed);
// 	sin_r[0] = sin(-rotate_speed);
// 	sin_r[1] = sin(rotate_speed);
// }

// static void
// 	calculate_sf_dist(double height, double *sf_dist)
// {
// 	int	i;

// 	i = 0;
// 	while (i < height)
// 	{
// 		sf_dist[i] = (height / (2 * (double)i - height));
// 		i++;
// 	}
// }

// void
// 	make_tables(t_game *game)
// {
// 	t_f_ray *ray;

	
// 	// calculate_camera_x(game->window.size.x, game->camera_x);
// 	// calculate_cos_sin(game->config.rotate_speed, game->cos, game->sin);
// 	// calculate_sf_dist(game->window.size.y, game->sf_dist);
// }
