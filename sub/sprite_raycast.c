/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_raycast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 04:35:17 by kfumiya           #+#    #+#             */
/*   Updated: 2021/06/03 20:35:32 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include "includes/key_macos.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define X_EVENT_KEY_PRESS	2
# define X_EVENT_KEY_RELEASE	3
#define X_EVENT_KEY_EXIT	17
#define texWidth 64
#define texHeight 64
#define mapWidth 24
#define mapHeight 24
#define width 640
#define height 480
#define numSprites 19

struct	Sprite
{
	double		x;
	double		y;
	int			texture;
};

struct Sprite	sprite[numSprites] =
{
	{20.5, 11.5, 10}, //green light in front of playerstart
	//green lights in every room
	{18.5,4.5, 10},
	{10.0,4.5, 10},
	{10.0,12.5,10},
	{3.5, 6.5, 10},
	{3.5, 20.5,10},
	{3.5, 14.5,10},
	{14.5,20.5,10},

	//row of pillars in front of wall: fisheye test
	{18.5, 10.5, 9},
	{18.5, 11.5, 9},
	{18.5, 12.5, 9},

	//some barrels around the map
	{21.5, 1.5, 8},
	{15.5, 1.5, 8},
	{16.0, 1.8, 8},
	{16.2, 1.2, 8},
	{3.5,  2.5, 8},
	{9.5, 15.5, 8},
	{10.0, 15.1,8},
	{10.5, 15.8,8},
};

int		spriteOrder[numSprites];
double	spriteDistance[numSprites];

typedef struct		s_pair
{
	double	first;
	int		second;
}					t_pair;

typedef struct s_pos_fl
{
	float x;
	float y;
} t_pos_fl;

typedef struct s_pos
{
	double x;
	double y;
} t_pos;

typedef struct s_w_ray
{
	double camerax;
	t_pos raydir;
	t_pos map;//int
	t_pos sidedist;
	t_pos deltadist;
	double p_walldist;
	t_pos step;//int
	int lineheight;
	int drawstart;
	int drawend;
	int texnum;
	double wallx;
	t_pos tex_pos;
	t_pos floorx_wall;
	double weight;
	t_pos currentfloor;
	t_pos floortex;//int
} t_w_ray;

typedef struct s_f_ray
{
	int horizon;
	float pos_z;
	float rowdist;
	t_pos_fl floorstep;
	t_pos_fl floor;
	t_pos_fl cell;//int
	t_pos_fl tex_pos;//int
} t_f_ray;

typedef struct	s_img
{
	void	*img;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}				t_img;

typedef struct	s_info
{
	t_pos pos;
	t_pos dir;
	t_pos plane;
	void	*mlx;
	void	*win;
	t_img	img;
	int		buf[height][width];
	int		**texture;
	double	moveSpeed;
	double	rotSpeed;
	int **map;
	// t_f_ray *f_ray;
	// t_w_ray *w_ray;
	// 
	int		key_a;
	int		key_w;
	int		key_s;
	int		key_d;
	int		key_esc;
	double	zBuffer[width];
}				t_info;

void	key_update(t_info *info);

static int	compare(const void *first, const void *second)
{
	if (*(int *)first > *(int *)second)
		return (1);
	else if (*(int *)first < *(int *)second)
		return (-1);
	else
		return (0);
}

void	sort_order(t_pair *orders, int amount)
{
	t_pair	tmp;

	for (int i = 0; i < amount; i++)
	{
		for (int j = 0; j < amount - 1; j++)
		{
			if (orders[j].first > orders[j + 1].first)
			{
				tmp.first = orders[j].first;
				tmp.second = orders[j].second;
				orders[j].first = orders[j + 1].first;
				orders[j].second = orders[j + 1].second;
				orders[j + 1].first = tmp.first;
				orders[j + 1].second = tmp.second;
			}
		}
	}
}

void	sortSprites(int *order, double *dist, int amount)
{
	t_pair	*sprites;

	//std::vector<std::pair<double, int>> sprites(amount);
	sprites = (t_pair*)malloc(sizeof(t_pair) * amount);
	for (int i = 0; i < amount; i++)
	{
		sprites[i].first = dist[i];
		sprites[i].second = order[i];
	}
	sort_order(sprites, amount);
	//std::sort(sprites.begin(), sprites.end());
	for (int i = 0; i < amount; i++)
	{
		dist[i] = sprites[amount - i - 1].first;
		order[i] = sprites[amount - i - 1].second;
	}
	free(sprites);
}

int	worldMap[mapWidth][mapHeight] =
									{
										{8,8,8,8,8,8,8,8,8,8,8,4,4,6,4,4,6,4,6,4,4,4,6,4},
										{8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
										{8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,6},
										{8,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
										{8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
										{8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,6,6,6,0,6,4,6},
										{8,8,8,8,0,8,8,8,8,8,8,4,4,4,4,4,4,6,0,0,0,0,0,6},
										{7,7,7,7,0,7,7,7,7,0,8,0,8,0,8,0,8,4,0,4,0,6,0,6},
										{7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,0,0,0,0,0,6},
										{7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,0,0,0,0,4},
										{7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,6,0,6,0,6},
										{7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,4,6,0,6,6,6},
										{7,7,7,7,0,7,7,7,7,8,8,4,0,6,8,4,8,3,3,3,0,3,3,3},
										{2,2,2,2,0,2,2,2,2,4,6,4,0,0,6,0,6,3,0,0,0,0,0,3},
										{2,2,0,0,0,0,0,2,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
										{2,0,0,0,0,0,0,0,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
										{1,0,0,0,0,0,0,0,1,4,4,4,4,4,6,0,6,3,3,0,0,0,3,3},
										{2,0,0,0,0,0,0,0,2,2,2,1,2,2,2,6,6,0,0,5,0,5,0,5},
										{2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
										{2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
										{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
										{2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
										{2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
										{2,2,2,2,1,2,2,2,2,2,2,1,2,2,2,5,5,5,5,5,5,5,5,5}
									};

void
	set_pos_fl(t_pos_fl *pos, float x, float y)
{
	pos->x = x;
	pos->y = y;
}

void
	set_pos(t_pos *pos, double x, double y)
{
	pos->x = x;
	pos->y = y;
}


int init_map(t_info *info)
{
	int i;
	int j;

	if (!(info->map = (int **)malloc(sizeof(int *) * mapHeight)))
		return (0);
	i = 0;
	while (i < mapHeight)
	{
		if (!(info->map[i] = malloc(sizeof(int) * mapWidth)))
			return (0);
		j = 0;
		while (j < mapWidth)
		{
			info->map[i][j] = worldMap[i][j];
			j++;
		}
		i++;
	}
	return (1);
}

void
	print_map(int **map)
{
	int i;
	int j;

	i = 0;
	while (i < mapHeight)
	{
		j = 0;
		while (j < mapWidth)
		{
			printf("%d", map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	draw(t_info *info)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			info->img.data[y * width + x] = info->buf[y][x];
		}
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}

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
	set_f_ray(t_info *info, t_f_ray *ray, int y)
{
	//左端の光線（x = 0）と右端の光線（x = w）のrayDir
	float rayDirX0;
	float rayDirY0;
	float rayDirX1;
	float rayDirY1;

	rayDirX0 = info->dir.x - info->plane.x;
	rayDirY0 = info->dir.y - info->plane.y;
	rayDirX1 = info->dir.x + info->plane.x;
	rayDirY1 = info->dir.y + info->plane.y;
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
	set_pos_fl(&ray->floor, info->pos.x + ray->rowdist * rayDirX0,
						info->pos.y + ray->rowdist * rayDirY0);
}

void
	draw_cf(t_info *info, t_f_ray *ray, int y)
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
		color = info->texture[floorTexture][texWidth * (int)ray->tex_pos.y + (int)ray->tex_pos.x];
		color = (color >> 1) & 8355711; // make a bit darker
		info->buf[y][x] = color;
		//天井（対称、screenHeight-y-1ではなくy）
		color = info->texture[ceilingTexture][texWidth * (int)ray->tex_pos.y + (int)ray->tex_pos.x];
		color = (color >> 1) & 8355711; // make a bit darker
		info->buf[height - y - 1][x] = color;
	}
}

void
	floor_cast(t_info *info)
{
	int y;
	t_f_ray ray;

	// info->f_ray = &ray;
	y = height / 2;
	init_f_ray(&ray);
	while (++y < height)
	{
		set_f_ray(info, &ray, y);
		draw_cf(info, &ray, y);
	}
}

void
	init_w_ray(t_w_ray *ray)
{
	ray->camerax = 0;
	set_pos(&ray->raydir, 0, 0);
	set_pos(&ray->map, 0, 0);
	set_pos(&ray->sidedist, 0, 0);
	set_pos(&ray->deltadist, 0, 0);
	ray->p_walldist = 0;
	set_pos(&ray->step, 0, 0);
	ray->lineheight = 0;
	ray->drawstart = 0;
	ray->drawend = 0;
	ray->texnum = 0;
	set_pos(&ray->tex_pos, 0, 0);
	set_pos(&ray->floorx_wall, 0, 0);
}

void
	set_w_ray(t_info *info, t_w_ray *ray, int x)
{
	ray->camerax = 2 * x / (double)width - 1;
	set_pos(&ray->raydir, info->dir.x + info->plane.x * ray->camerax,
							info->dir.y + info->plane.y * ray->camerax);
	set_pos(&ray->map, (int)info->pos.x, (int)info->pos.y);
	set_pos(&ray->deltadist, 
				fabs(1 / ray->raydir.x), fabs(1 / ray->raydir.y));
	if (ray->raydir.x < 0)
	{
		ray->step.x = -1;
		ray->sidedist.x = (info->pos.x - (int)ray->map.x) * ray->deltadist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->sidedist.x = ((int)ray->map.x + 1.0 - info->pos.x) * ray->deltadist.x;
	}
	if (ray->raydir.y < 0)
	{
		ray->step.y = -1;
		ray->sidedist.y = (info->pos.y - (int)ray->map.y) * ray->deltadist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->sidedist.y = ((int)ray->map.y + 1.0 - info->pos.y) * ray->deltadist.y;
	}
}

void
	wall_hit(t_info *info, t_w_ray *ray, int *hit, int *side)
{
	while (*hit == 0)
	{
		//jump to next map square, OR in x-direction, OR in y-direction
		if (ray->sidedist.x < ray->sidedist.y)
		{
			ray->sidedist.x += ray->deltadist.x;
			ray->map.x += ray->step.x;
			*side = 0;
		}
		else
		{
			ray->sidedist.y += ray->deltadist.y;
			ray->map.y += ray->step.y;
			*side = 1;
		}
		//Check if ray has hit a wall
		if (info->map[(int)ray->map.x][(int)ray->map.y] > 0)
			*hit = 1;
	}
	if (*side == 0)
		ray->p_walldist = ((int)ray->map.x - info->pos.x + (1 - ray->step.x) / 2) / ray->raydir.x;
	else
		ray->p_walldist = ((int)ray->map.y - info->pos.y + (1 - ray->step.y) / 2) / ray->raydir.y;

}

void
	calculate_draw(t_info *info, t_w_ray *ray, int *side)
{
	//Calculate height of line to draw on screen
	ray->lineheight = (int)(height / ray->p_walldist);
	ray->drawstart= -(ray->lineheight) / 2 + height / 2;
	if(ray->drawstart < 0)
		ray->drawstart = 0;
	ray->drawend = ray->lineheight / 2 + height / 2; 
	if(ray->drawend >= height)
		ray->drawend = height - 1;

	// texturing calculations
	ray->texnum = info->map[(int)ray->map.x][(int)ray->map.y] - 1;
	// calculate value of wallX
	if (*side == 0)
		ray->wallx = info->pos.y + ray->p_walldist * ray->raydir.y;
	else
		ray->wallx = info->pos.x + ray->p_walldist * ray->raydir.x;
	ray->wallx -= floor(ray->wallx);

	// x coordinate on the texture
	ray->tex_pos.x = (int)(ray->wallx * (double)texWidth);
	if (*side == 0 && ray->raydir.x > 0)
		ray->tex_pos.x = texWidth - (int)ray->tex_pos.x - 1;
	if (*side == 1 && ray->raydir.y < 0)
		ray->tex_pos.x = texWidth - (int)ray->tex_pos.x - 1;
}

void
	draw_wall(t_info *info, t_w_ray *ray, int x, int side)
{
	double step;
	double texpos;

	// How much to increase the texture coordinate perscreen pixel
	step = 1.0 * texHeight / ray->lineheight;
	// Starting texture coordinate
	texpos = (ray->drawstart - height / 2 + ray->lineheight / 2) * step;
	for (int y = ray->drawstart; y < ray->drawend; y++)
	{
		// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		ray->tex_pos.y = (int)texpos & (texHeight - 1);
		texpos += step;

		int color = info->texture[ray->texnum][texHeight * (int)ray->tex_pos.y + (int)ray->tex_pos.x];

		// make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		if (side == 1)
			color = (color >> 1) & 8355711;
		info->buf[y][x] = color;
	}
	info->zBuffer[x] = ray->p_walldist; //perpendicular distance is used
}

void
	wall_cast(t_info *info)
{
	int x;
	int hit; //was there a wall hit?
	int side; //was a NS or a EW wall hit?
	t_w_ray ray;

	x = -1;
	init_w_ray(&ray);
	while (++x < width)
	{
		hit = 0;
		side = 0;
		set_w_ray(info, &ray, x);
		wall_hit(info, &ray, &hit, &side);
		calculate_draw(info, &ray, &side);
		draw_wall(info, &ray, x, side);
	}
}

void
	sprite_cast(t_info *info)
{
	for(int i = 0; i < numSprites; i++)
	{
		spriteOrder[i] = i;
		spriteDistance[i] = ((info->pos.x - sprite[i].x) * (info->pos.x - sprite[i].x) + (info->pos.y - sprite[i].y) * (info->pos.y - sprite[i].y)); //sqrt not taken, unneeded
	}
	sortSprites(spriteOrder, spriteDistance, numSprites);
	//スプライトを並べ替えた後、投影を実行して描画します
	for(int i = 0; i < numSprites; i++)
	{
		//スプライトの位置をカメラを基準にして変換します
		double spriteX = sprite[spriteOrder[i]].x - info->pos.x;
		double spriteY = sprite[spriteOrder[i]].y - info->pos.y;

		//逆カメラ行列でスプライトを変換します
		// [ plane.x   dir.x ] -1                                       [ dir.y      -dir.x ]
		// [               ]       =  1/(plane.x*dir.y-dir.x*plane.y) *   [                 ]
		// [ plane.y   dir.y ]                                          [ -plane.y  plane.x ]

		double invDet = 1.0 / (info->plane.x * info->dir.y - info->dir.x * info->plane.y); //required for correct matrix multiplication

		double transformX = invDet * (info->dir.y * spriteX - info->dir.x * spriteY);
		double transformY = invDet * (-info->plane.y * spriteX + info->plane.x * spriteY); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])

		int spriteScreenX = (int)((width / 2) * (1 + transformX / transformY));

		//スプライトをスケーリングおよび移動するためのパラメータ
		#define uDiv 1
		#define vDiv 1
		#define vMove 0.0
		int vMoveScreen = (int)(vMove / transformY);

		//画面上のスプライトの高さを計算します
		int spriteHeight = (int)fabs((height / transformY) / vDiv); //using "transformY" instead of the real distance prevents fisheye
		//現在のストライプを埋めるために最低ピクセルと最高ピクセルを計算します
		int drawStartY = -spriteHeight / 2 + height / 2 + vMoveScreen;
		if(drawStartY < 0) drawStartY = 0;
		int drawEndY = spriteHeight / 2 + height / 2 + vMoveScreen;
		if(drawEndY >= height) drawEndY = height - 1;

		//スプライトの幅を計算します
		int spriteWidth = (int)fabs((height / transformY) / uDiv);
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0) drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= width) drawEndX = width - 1;

		//画面上のスプライトのすべての垂直ストライプをループします
		for(int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)((256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256);
			// ifの条件は次のとおりです。
			// 1）カメラ面の前にあるので、後ろに物が見えません
			// 2）画面上にあります（左）
			// 3）画面上にあります（右）
			// 4）ZBuffer、垂直距離
			if(transformY > 0 && stripe > 0 && stripe < width && transformY < info->zBuffer[stripe])
			for(int y = drawStartY; y < drawEndY; y++) //現在のストライプのすべてのピクセル
			{
				int d = (y-vMoveScreen) * 256 - height * 128 + spriteHeight * 128; //フロートを回避するための256および128の要素
				int texY = ((d * texHeight) / spriteHeight) / 256;
				int color = info->texture[sprite[spriteOrder[i]].texture][texWidth * texY + texX]; //テクスチャから現在の色を取得します
				if((color & 0x00FFFFFF) != 0) info->buf[y][stripe] = color; //ピクセルが黒でない場合はペイントし、黒は非表示の色です
			}
		}
	}
}

void	calc(t_info *info)
{
	//FLOOR CASTING
	floor_cast(info);
	
	// WALL CASTING
	wall_cast(info);

	//スプライトキャスティング
	//スプライトを遠くから閉じるように並べ替えます
	sprite_cast(info);
}

int	main_loop(t_info *info)
{
	calc(info);
	draw(info);
	key_update(info);
	return (0);
}

void	key_update(t_info *info)
{
	if (info->key_w)
	{
		if (!worldMap[(int)(info->pos.x + info->dir.x * info->moveSpeed)][(int)(info->pos.y)])
			info->pos.x += info->dir.x * info->moveSpeed;
		if (!worldMap[(int)(info->pos.x)][(int)(info->pos.y + info->dir.y * info->moveSpeed)])
			info->pos.y += info->dir.y * info->moveSpeed;
	}
	//move backwards if no wall behind you
	if (info->key_s)
	{
		if (!worldMap[(int)(info->pos.x - info->dir.x * info->moveSpeed)][(int)(info->pos.y)])
			info->pos.x -= info->dir.x * info->moveSpeed;
		if (!worldMap[(int)(info->pos.x)][(int)(info->pos.y - info->dir.y * info->moveSpeed)])
			info->pos.y -= info->dir.y * info->moveSpeed;
	}
	//rotate to the right
	if (info->key_d)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = info->dir.x;
		info->dir.x = info->dir.x * cos(-info->rotSpeed) - info->dir.y * sin(-info->rotSpeed);
		info->dir.y = oldDirX * sin(-info->rotSpeed) + info->dir.y * cos(-info->rotSpeed);
		double oldPlaneX = info->plane.x;
		info->plane.x = info->plane.x * cos(-info->rotSpeed) - info->plane.y * sin(-info->rotSpeed);
		info->plane.y = oldPlaneX * sin(-info->rotSpeed) + info->plane.y * cos(-info->rotSpeed);
	}
	//rotate to the left
	if (info->key_a)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = info->dir.x;
		info->dir.x = info->dir.x * cos(info->rotSpeed) - info->dir.y * sin(info->rotSpeed);
		info->dir.y = oldDirX * sin(info->rotSpeed) + info->dir.y * cos(info->rotSpeed);
		double oldPlaneX = info->plane.x;
		info->plane.x = info->plane.x * cos(info->rotSpeed) - info->plane.y * sin(info->rotSpeed);
		info->plane.y = oldPlaneX * sin(info->rotSpeed) + info->plane.y * cos(info->rotSpeed);
	}
	if (info->key_esc)
		exit(0);
}

int		key_press(int key, t_info *info)
{
	if (key == K_ESC)
		exit(0);
	else if (key == K_W)
		info->key_w = 1;
	else if (key == K_A)
		info->key_a = 1;
	else if (key == K_S)
		info->key_s = 1;
	else if (key == K_D)
		info->key_d = 1;
	return (0);
}

int		key_release(int key, t_info *info)
{
	if (key == K_ESC)
		exit(0);
	else if (key == K_W)
		info->key_w = 0;
	else if (key == K_A)
		info->key_a = 0;
	else if (key == K_S)
		info->key_s = 0;
	else if (key == K_D)
		info->key_d = 0;
	return (0);
}

void	load_image(t_info *info, int *texture, char *path, t_img *img)
{
	img->img = mlx_xpm_file_to_image(info->mlx, path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
	for (int y = 0; y < img->img_height; y++)
	{
		for (int x = 0; x < img->img_width; x++)
		{
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
		}
	}
	mlx_destroy_image(info->mlx, img->img);
}

void	load_texture(t_info *info)
{
	t_img	img;

	load_image(info, info->texture[0], "textures/eagle.xpm", &img);
	load_image(info, info->texture[1], "textures/redbrick.xpm", &img);
	load_image(info, info->texture[2], "textures/purplestone.xpm", &img);
	load_image(info, info->texture[3], "textures/greystone.xpm", &img);
	load_image(info, info->texture[4], "textures/bluestone.xpm", &img);
	load_image(info, info->texture[5], "textures/mossy.xpm", &img);
	load_image(info, info->texture[6], "textures/wood.xpm", &img);
	load_image(info, info->texture[7], "textures/colorstone.xpm", &img);
	load_image(info, info->texture[8], "textures/barrel.xpm", &img);
	load_image(info, info->texture[9], "textures/pillar.xpm", &img);
	load_image(info, info->texture[10], "textures/greenlight.xpm", &img);
}


int	main(void)
{
	t_info info;
	info.mlx = mlx_init();

	init_map(&info);
	// print_map(info.map);
	
	set_pos(&info.pos, 22.0, 11.5);
	set_pos(&info.dir, -1, 0);
	set_pos(&info.plane, 0, 0.66);
	info.moveSpeed = 0.05;
	info.rotSpeed = 0.05;
	info.key_a = 0;
	info.key_w = 0;
	info.key_s = 0;
	info.key_d = 0;
	info.key_esc = 0;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			info.buf[i][j] = 0;
		}
	}

	if (!(info.texture = (int **)malloc(sizeof(int *) * 11)))
		return (-1);
	for (int i = 0; i < 11; i++)
	{
		if (!(info.texture[i] = (int *)malloc(sizeof(int) * (texHeight * texWidth))))
			return (-1);
	}
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < texHeight * texWidth; j++)
		{
			info.texture[i][j] = 0;
		}
	}

	load_texture(&info);
	
	info.win = mlx_new_window(info.mlx, width, height, "mlx");

	info.img.img = mlx_new_image(info.mlx, width, height);
	info.img.data = (int *)mlx_get_data_addr(info.img.img, &info.img.bpp, &info.img.size_l, &info.img.endian);
	
	mlx_loop_hook(info.mlx, &main_loop, &info);
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);
	mlx_hook(info.win, X_EVENT_KEY_RELEASE, 0, &key_release, &info);

	mlx_loop(info.mlx);
}
