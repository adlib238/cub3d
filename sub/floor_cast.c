/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_cast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 07:45:27 by kfumiya           #+#    #+#             */
/*   Updated: 2021/06/06 09:09:32 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	init_f_ray(t_f_ray *ray)
{
	ray->horizon = 0;
	ray->pos_z = 0;
	ray->rowdist = 0;
	set_pos_fl(&ray->floorstep, 0, 0);
	set_pos_fl(&ray->floor, 0, 0);
	set_pos_fl(&ray->cell, 0, 0);
	set_pos_fl(&ray->tex_pos, 0, 0);
}

void
	set_f_ray(t_game *game, t_f_ray *ray, int y)
{
	//左端の光線（x = 0）と右端の光線（x = w）のrayDir
	float rayDirX0;
	float rayDirY0;
	float rayDirX1;
	float rayDirY1;

	rayDirX0 = game->dir.x - game->plane.x;
	rayDirY0 = game->dir.y - game->plane.y;
	rayDirX1 = game->dir.x + game->plane.x;
	rayDirY1 = game->dir.y + game->plane.y;
	//画面の中心（地平線）と比較した現在のy位置
	ray->horizon = y - height / 2;
	//カメラの垂直位置。
	ray->pos_z = 0.5 * height;
	//現在の行のカメラから床までの水平距離。 0.5は、床と天井のちょうど真ん中のz位置です。
	ray->rowdist = ray->pos_z / ray->horizon;
	//各xに追加する必要のある実世界のステップベクトルを計算します（カメラ平面に平行） 段階的に追加すると、内側のループで重みを使用した乗算が回避されます
	set_pos_fl(&ray->floorstep, 
		ray->rowdist * (rayDirX1 - rayDirX0) / width,
		ray->rowdist * (rayDirY1 - rayDirY0) / width);
	//左端の列の実世界の座標。これは、右に進むにつれて更新されます。
	set_pos_fl(&ray->floor, game->pos.x + ray->rowdist * rayDirX0,
						game->pos.y + ray->rowdist * rayDirY0);
}

void
	draw_cf(t_game *game, t_f_ray *ray, int y)
{
	int color;
	int x;

	x = -1;
	while (++x < width)
	{
		//セル座標はfloorXとfloorYの整数部分から単純に取得されます
		set_pos_fl(&ray->cell, (int)(ray->floor.x), (int)(ray->floor.y));
		//小数部分からテクスチャ座標を取得します
		set_pos_fl(&ray->tex_pos,
				(int)(texWidth * (ray->floor.x - ray->cell.y)) & (texWidth - 1),
				(int)(texHeight * (ray->floor.y - ray->cell.y)) & (texHeight - 1));
		ray->floor.x += ray->floorstep.x;
		ray->floor.y += ray->floorstep.y;
		//テクスチャを選択し、ピクセルを描画します
		int checkerBoardPattern = (int)(ray->cell.x + ray->cell.y) & 1;
		int floorTexture;
		if(checkerBoardPattern == 0) floorTexture = 3;
		else floorTexture = 4;
		int ceilingTexture = 6;
		// floor
		color = info->texture[][texWidth * (int)ray->tex_pos.y + (int)ray->tex_pos.x];
		color = (color >> 1) & 8355711; // make a bit darker
		info->buf[y][x] = color;
		//天井（対称、screenHeight-y-1ではなくy）
		color = info->texture[ceilingTexture][texWidth * (int)ray->tex_pos.y + (int)ray->tex_pos.x];
		color = (color >> 1) & 8355711; // make a bit darker
		info->buf[height - y - 1][x] = color;
	}
}

void
	floor_cast(t_game *game)
{
	int y;
	t_f_ray ray;

	// info->f_ray = &ray;
	y = height / 2;
	init_f_ray(&ray);
	while (++y < height)
	{
		set_f_ray(game, &ray, y);
		draw_cf(game, &ray, y);
	}
}
