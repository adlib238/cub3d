/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 18:25:53 by kfumiya           #+#    #+#             */
/*   Updated: 2022/06/02 13:06:08 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <stdbool.h>
# include "../libft/includes/libft.h"
# include "../mlx_linux/mlx.h"
# include "../mlx_linux/mlx_new_window.h"
# include "../mlx_linux/mlx_opengl.h"
# include "../mlx_linux/mlx_png.h"
// # include "../mlx/mlx.h"

# define MAX(a, b)	((a > b) ? a : b)
# define MIN(a, b)	((a < b) ? a : b)


# define ERROR	-1
# define MAX_MAP_W 200
# define MAX_MAP_H 200
# define MOVE_PX (0.033)
# define ROTATE_RAD (M_PI / 300)

# define KEY_A			0
# define KEY_S			1
# define KEY_D			2
# define KEY_W			13
# define KEY_LEFT		123
# define KEY_RIGHT		124
# define KEY_ESC		53
# define KEY_Q			12
/* 
# define MAX(a, b)			((a > b) ? a : b)
# define FINT(x)			((int)floor(x))
# define CHECK_TOP(p)		(FINT(p.x) >= 0 && FINT(p.y) >= 0)
# define CHECK_BOT(p, c)	(FINT(p.x) < (c).columns && FINT(p.y) < (c).rows)
# define IN_MAP(p, c)		(CHECK_TOP(p) && CHECK_BOT(p, c))
# define MAP(p, c)			(c).map[(FINT(p.x))][(FINT(p.y))]

# define FLAG_SHADOWS		0x00000100

# define DIRECTIONS "NSEW"
# define VALID_MAP_CHARACTERS " 012NSEW"


# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_EXIT			17

# define C_R				0
# define C_NO				1
# define C_SO				2
# define C_WE				3
# define C_EA				4
# define C_S				5
# define C_F				6
# define C_C				7
# define C_MAP				8
# define C_LAST				9

# define TEXTURES			7
# define TEX_NORTH			0
# define TEX_SOUTH			1
# define TEX_WEST			2
# define TEX_EAST			3
# define TEX_SPRITE			4
# define TEX_CEILING		5
# define TEX_FLOOR			6

 */


// 描画するためのイメージ情報を保持
typedef struct	s_img {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
} t_img;

// Vector2D
typedef struct	s_vec {
	double		x;
	double		y;
} t_vec2;

// Ray 2D
typedef struct	s_ray2 {
	t_vec2		pos;  // レイの始点の位置ベクトル
	t_vec2		way;  // レイの始点から伸びる方向ベクトル
} t_ray2;

// Player
typedef struct	s_player {
	t_vec2		pos;  // 現在位置(px)[x, y]
	t_vec2		dir;       // 現在向いている方向のベクトル
	t_vec2		plane;     // 2Dレイキャスティング用のカメラ平面
	int			is_moving; // 動くキーが押されているか (W=1, S=-1, None=0)
	int			is_sidling;  // 動くキーが押されているか (D=1, A=-1, None=0)
	int			is_rotating; // 動くキーが押されているか (左矢印=1, 右矢印=-1, None=0)
} t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		img;
	int			screen_width;
	int			screen_height;
	t_player	player;
	char		**map;
	int			map_row;
	int			map_col;
	t_img		tex_n; // 北
	t_img		tex_s; // 南
	t_img		tex_w; // 西
	t_img		tex_e; // 東
	int			tex_width;
	int			tex_height;
	uint32_t	sky_color;
	uint32_t	ground_color;
	double		horizon;
	double		*z_buffer;
} t_game;

// レイキャスト
typedef struct	s_ray {
	// カメラ平面上のx座標 (3D表示時の画面のx座標)  -1.0~1.0
	double		camera_x;
	// 光線ベクトル
	t_vec2		dir;
	// map: 現在対象としているマップ内の正方形を表す
	int			map_x;
	int			map_y;
	// sideDistは, 光線が開始位置から最初の次の正方形に移動するまでの距離
	double		side_dist_x;
	double		side_dist_y;
	// perpWallDistは, 当たった壁とカメラ平面ベクトルとの距離を表す (perpはperpendicular(垂直)の略)
	double		perp_wall_dist;
	// 壁のx面かy面どちらに当たったかを判断するための変数  0: x面, 1: y面
	int			side;
	// stepはx,yそれぞれ正か負かどちらの方向に進むか記録する (必ず +1 or -1)
	int			step_x;
	int			step_y;
	// deltaDistは, 光線が今の正方形から次の正方形に行くために移動する距離
	double		delta_dist_x;
	double		delta_dist_y;
	// texは当たったテクスチャ
	t_img		*tex;
} t_ray;

// 壁を描画するのに必要な情報を保持する構造体
typedef struct	s_wall
{
	// スクリーンに描画する必要のある縦線の長さを求める
	int			line_height;
	// 実際に描画すべき場所の開始位置
	int			draw_start;
	// 実際に描画すべき場所の位置
	int			draw_end;
	// 正確なx座標 (整数型ではない)
	double		wall_x;
	// テクスチャ上のx座標 (0~TEXTURE_WIDTH)
	int			texture_x;
	// y方向の1ピクセルごとにテクスチャのy座標が動く量
	double		step;
	// テクスチャの現在のy座標
	double		texture_pos_y;
	// テクスチャの現在のy座標(double型)を整数型に変換する.
	int			texture_y;
} t_wall;

/* degug.c */
void print_config(t_game *game);

/* errors.c */
int return_error_msg(char *msg);
void put_err_msg(char *msg);
/* game.c */
int init_game(t_game *game);
void set_screen(t_game *game, int save);
int main_loop(t_game *game);
/* read_cub.c */
int read_cub(t_game *game, char *path);
/* set_free.c */
void set_free(void **dst, void *src);
void instant_free(void **strs);
/* utils.c */
bool str_isvalid_set(char *str, int (*f)(int));
int strs_size(char **strs);
/* set_resolution.c */
int set_resolution(t_game *game, char *w, char *h);
/* set_color.c */
int set_color(t_game *game, char c, char *rgb);
/* read_texture.c */
int read_texture(t_game *game, char *s, char *path);
bool is_texture(char *s);
/* read_map.c */
int read_map(t_game *game, char *line);
/* readline.c */
char *readline(int fd);
/* check_map.c */
int check_map(t_game *game);
/* draw_wall.c */
void init_ray(t_game *game, t_ray *ray, int x);
void raycast(t_game *game, t_ray *ray);
void cal_screen_info(t_game *game, t_ray ray, t_wall *wall);
void draw_stripe(t_game *game, t_ray ray, t_wall *wall, int x);
void draw_walls(t_game *game);
/* update_player.c */
void update_player(t_game *game);
/* vector.c */
double vec_length(t_vec2 vec);
double deg_rad(int x);
void vec_rotate(t_vec2 *vec, double rad);
/* wall_utils.c */
void set_texture(t_game *game, t_ray *ray);
/* set_free.c */
void set_free(void **dst, void *src);
void instant_free(void **strs);
/* draw.c */
void reset_img(t_img *img);
/* init_player.c */
void init_player(t_player *player, double x, double y, char dir);


/* hooks.c */
int close_window(t_game *game);
int key_press(int keycode, t_game *game);
int key_release(int keycode, t_game *game);
/* mlx_utils.c */
int read_image(t_game *game, t_img *img, char *filepath);
void my_mlx_pixel_put(t_img *img, int x, int y, int color);
uint32_t get_color(t_img img, int x, int y);



/* 
void init_game(t_game *game, int save);
int exit_game(t_game *game, int code);
int parse_config(t_game *game, char *flie_path);
int clear_config(t_config *config);
void init_config(t_config *config);
int parse_line(t_config *config, char const *line, t_str **map_buffer);
int parse_dimensions(t_config *config, int key, char const *line);
int parse_textures(t_config *config, int key, char const *line);
int parse_color(t_config *config, int key, char const *line);
int parse_map(t_config *config, t_str *map_buffer, t_game *game);
int get_max_rows(t_str *map_buffer);
int get_max_columns(t_str *map_buffer);
int check_valid(t_config *config, t_str *map_buffer);
int init_map(t_config *config);
void modify_map(t_config *config, t_str *map_buffer);
void check_map(t_config *config, int x, int y, int *code);
int get_sprites(t_game *game);
int start_game(t_game *game);
int init_window(t_window *window, t_config *config);
int init_image(t_window *window, t_image *img);
int clear_window(t_window *window);
int load_textures(t_game *game);
void clear_textures(t_game *game);
int get_tex_color(t_tex *tex, t_pos *pos);
void clear_sprites(t_sprite **sprites);
void set_start_pos(t_config *config, t_camera *camera);
void set_start_angle(t_config *config, t_camera *camera);
void make_tables(t_game *game);
int screenshot(t_game *game);
void update_screen(t_game *game);
int draw_rectangle(t_window *window, t_pos *p1, t_pos *p2, int color);
void	draw_pixel(t_window *w, t_pos *pos, int color);
void raycast(t_game *game, t_ray *ray, int column);
void draw_wall(t_game *game, t_ray *ray);
void draw_ceiling_floor(t_game *game, t_ray *ray);
int move_camera(t_game *game, int direction);
int move_perp_camera(t_game *game, int direction);
int rotate_camera(t_game *game, int dir);
int key_press(int keycode, t_game *game);
int key_release(int keycode, t_game *game);
int exit_hook(t_game *game);
int main_loop(t_game *game);
void update_window(t_game *game);
int distance_shade(int options, int color, double distance);
int shade_color(int color, double divide);
int draw_vertical_line(t_window *window, t_pos *start,
								int length, int color);
 */
#endif
