/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:36:23 by kfumiya           #+#    #+#             */
/*   Updated: 2022/05/31 14:33:01 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	init_ray(t_game *game, t_ray *ray, int x)
{
	// カメラ平面上のx座標（３D表示時の画面のx座標）　-1.0~1.0
	ray->camera_x = 2 * x / (double)game->screen_width - 1;
	ray->dir.x = game->player.dir.x + game->player.plane.x * ray->camera_x;
	ray->dir.y = game->player.dir.y + game->player.plane.y * ray->camera_x;
	// map: 現在対象としているマップ内の正方形を表す
	ray->map_x = (int)game->player.pos.x;
	ray->map_y = (int)game->player.pos.y;
	// delta_distは光線が今の正方形から次の正方形に行くために移動する距離
	// 今回は比率だけ必要なため、簡略化した形でも大丈夫
	ray->delta_dist_x = fabs(1 / ray->dir.x);
	ray->delta_dist_y = fabs(1 / ray->dir.y);
	// stepとside_distを求める
	ray->step_x = 1;
	ray->side_dist_x = (ray->map_x + 1.0 - game->player.pos.x)
		* ray->delta_dist_x;
	ray->step_y = 1;
	ray->side_dist_y = (ray->map_y + 1.0 - game->player.pos.y)
		* ray->delta_dist_y;
	// 光線ベクトルが負の場合
	if (ray->dir.x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.pos.x - ray->map_x)
			* ray->delta_dist_x;
	}
	if (ray->dir.y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.pos.x - ray->map_y)
			* ray->delta_dist_y;
	}
}

void
	raycast(t_game *game, t_ray *ray)
{
	// 光線が壁にぶつかるまで光線を進める
	while (game->map[ray->map_x][ray->map_y] != '1')
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
	}
	// 壁までの光線の距離を計算
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - game->player.pos.x \
			+ (1 - ray->step_x) / 2) / ray->dir.x;
	else
		ray->perp_wall_dist = (ray->map_y - game->player.pos.y \
			+ (1 - ray->step_y) / 2) / ray->dir.y;
	// 壁に当たった方角のテクスチャを設定
	set_texture(game, ray);
}

void
	cal_screen_info(t_game *game, t_ray ray, t_wall *wall)
{
	// スクリーンに描画する必要のある縦線の長さを求める
	wall->line_height = (int)(game->horizon / ray.perp_wall_dist);
	// 実際に描画すべき場所の開始位置と終了位置の計算
	wall->draw_start = -wall->line_height / 2 + game->screen_height / 2;
	if (wall->draw_start < 0)
		wall->draw_start = 0;
	wall->draw_end = wall->line_height / 2 + game->screen_height / 2;
	if (wall->draw_end >= game->screen_height)
		wall->draw_end = game->screen_height - 1;
	// 当たった壁上の正確なx座標を求める
	if (ray.side == 0)
		wall->wall_x = game->player.pos.y + ray.perp_wall_dist * ray.dir.y;
	else
		wall->wall_x = game->player.pos.x + ray.perp_wall_dist * ray.dir.x;
	wall->wall_x -= floor(wall->wall_x);
	// テクスチャ上のx座標（0~TEXTURE_WIDTH）
	wall->texture_x = (int)(wall->wall_x * ray.tex->width);
	if ((ray.side == 0 && ray.dir.x < 0) || (ray.side == 1 && ray.dir.y > 0))
		wall->texture_x = ray.tex->width - wall->texture_x - 1;
	// 各ピクセルのどのテクスチャのピクセルを描画するか計算する
	// y方向の１ピクセルごとにテクスチャのy座標が動く量
	wall->step = 1.0 * ray.tex->height / (double)wall->line_height;
}

void
	draw_stripe(t_game *game, t_ray ray, t_wall *wall, int x)
{
	uint32_t	color;
	int			y;

	// get_colorを有効にした時color = 0, x++, x--を削除;
	color = 0;
	x++;
	x--;
	// テクスチャの現在のy座標
	wall->texture_y = (wall->draw_start - game->screen_height / 2 \
			+ wall->line_height / 2) * wall->step;
	y = 0;
	while (y < game->screen_height)
	{
		// if (y <= game->screen_height / 2)
		// 	my_mlx_pixel_put(&game->img, x, y, game->sky_color);
		// else
		// 	my_mlx_pixel_put(&game->img, x, y, game->ground_color);
		// テクスチャの現在の座標（double型）を整数型に変換
		// （TEXTURE_HEGHT - 1）とのANDによりテクスチャ座標がテクスチャの高さを超えないようにしている
		if (y >= wall->draw_start && y < wall->draw_end)
		{
			wall->texture_y = (int)wall->texture_pos_y;
			if (wall->texture_y >= ray.tex->height)
				wall->texture_y = ray.tex->height - 1;
			wall->texture_pos_y += wall->step;
			// color = get_color(*ray.tex, wall->texture_x, wall->texture_y);
			// 正方形のyめんにヒットしていた場合はRGBのそれぞれを1/2にすることで暗くする
			if (ray.side == 1)
				color = (color >> 1) & 0x7f7f7f;
			// my_mlx_pixel_put(&game->img, x, y, color);
		}
		y++;
	}
}

void
	draw_walls(t_game *game)
{
	int		x;
	t_ray	ray;
	t_wall	wall;

	x = 0;
	// スクリーンの全てのxについて計算する
	while (x < game->screen_width)
	{
		// 初期設定
		init_ray(game, &ray, x);
		// 壁まで光線を飛ばす
		raycast(game, &ray);
		game->z_buffer[x] = ray.perp_wall_dist;
		// 描画
		cal_screen_info(game, ray, &wall);
		draw_stripe(game, ray, &wall, x);
		x++;
	}
}
