/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 21:30:12 by kfumiya           #+#    #+#             */
/*   Updated: 2022/05/31 11:52:00 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	init_game(t_game *game)
{
	// game->mlx = mlx_init();
	// game->win = NULL;
	game->screen_width = 0;
	game->screen_height = 0;
	game->player.pos.x = -1;
	game->player.pos.y = -1;
	if (!(game->map = ft_calloc(MAX_MAP_H, sizeof(char *)))) // 200 * 200が最大MAPサイズ
		return (return_error_msg("failed malloc"));
	game->map_row = 0;
	game->map_col = 0;
	game->tex_n.img = NULL;
	game->tex_s.img = NULL;
	game->tex_w.img = NULL;
	game->tex_e.img = NULL;
	game->tex_width = 0;
	game->tex_height = 0;
	game->sky_color = UINT32_MAX;
	game->ground_color = UINT32_MAX;
	game->horizon = 0;
	return (0);
}

void
	set_screen(t_game *game, int save)
{
	double	plane_length;
	int		max_w;
	int		max_h;

	// mlx_get_screen_sizeが有効になったらmax_w, max_hの初期化は消す
	max_w = 200;
	max_h = 200;
	// mlx_get_screen_size(game->mlx, &max_w, &max_h);
	// printf("Display size\n\twidth: %d\n\theight: %d\n", max_w, max_h);
	if (!save)
	{
		game->screen_width = MIN(game->screen_width, max_w);
		game->screen_height = MIN(game->screen_height, max_h);
		// game->win = mlx_new_window(game->mlx, game->screen_width,
		// 	game->screen_height, "cub3D");
	}
	// game->img.img = mlx_new_image(game->mlx, game->screen_width,
	// 	game->screen_height);
	// game->img.addr = mlx_get_data_addr(game->img.img,
	// 	&game->img.bits_per_pixel, &game->img.line_length, &game->img.endian);
	game->img.width = game->screen_width;
	game->img.height = game->screen_height;
	game->tex_width = game->tex_n.width;
	game->tex_height = game->tex_n.height;
	// planeベクトルの大きさを求める
	plane_length = vec2_length(game->player.plane);
	// 基準となる高さ、視野角に応じて横幅が変わってしますので、視野角の逆数をかけて１に戻す
	game->horizon = (double)game->screen_width * (1 / (2 * plane_length));
	// mlx_do_key_autorepeaton(game->mlx);
}

int
	main_loop(t_game *game)
{
	reset_img(&game->img);
	draw_walls(game);
	// draw_minimap(game);
	// update_player(game);
	// print_game(game);
	// mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}