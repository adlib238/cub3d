/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 10:46:15 by kfumiya           #+#    #+#             */
/*   Updated: 2022/05/27 11:06:27 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	close_window(t_game *game)
{
	// mlx_destroy_window(game->mlx, game->win);
	exit(0);
}

int
	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC || keycode == KEY_Q)
	{
		// mlx_destroy_window(game->mlx, game->win);
		exit(0);
	}
	if (keycode == KEY_W)
		game->player.is_moving = 1;
	if (keycode == KEY_S)
		game->player.is_moving = -1;
	if (keycode == KEY_A)
		game->player.is_sidling = -1;
	if (keycode == KEY_D)
		game->player.is_sidling = 1;
	if (keycode == KEY_LEFT)
		game->player.is_rotating = -1;
	if (keycode == KEY_RIGHT)
		game->player.is_rotating = 1;
	return (0);
}

int
	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W || keycode == KEY_S)
		game->player.is_moving = 0;
	if (keycode == KEY_A || keycode == KEY_D)
		game->player.is_sidling = 0;
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		game->player.is_rotating = 0;
	return (0);
}
