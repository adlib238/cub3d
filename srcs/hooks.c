/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:09:27 by kfumiya           #+#    #+#             */
/*   Updated: 2022/06/14 10:49:37 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	exit_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
}

int
	key_press(int keycode, t_data *data)
{
	if (keycode == KEY_ESC || keycode == KEY_Q)
		close_window(data);
	if (keycode == KEY_W)
		data->player.is_moving = 1;
	if (keycode == KEY_S)
		data->player.is_moving = -1;
	if (keycode == KEY_D)
		data->player.is_sidling = 1;
	if (keycode == KEY_A)
		data->player.is_sidling = -1;
	if (keycode == KEY_LEFT)
		data->player.is_rotating = -1;
	if (keycode == KEY_RIGHT)
		data->player.is_rotating = 1;
	return (0);
}

int
	key_release(int keycode, t_data *data)
{
	if (keycode == KEY_W || keycode == KEY_S)
		data->player.is_moving = 0;
	if (keycode == KEY_A || keycode == KEY_D)
		data->player.is_sidling = 0;
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		data->player.is_rotating = 0;
	return (0);
}
