/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 18:25:53 by kfumiya           #+#    #+#             */
/*   Updated: 2022/05/23 15:18:34 by kfumiya          ###   ########.fr       */
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
# include "../mlx/mlx.h"

# define ERROR				-1
# define MAX_MAP_WIDTH 200
# define MAX_MAP_HEIGHT 200

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

# define KEY_A			0
# define KEY_S			1
# define KEY_D			2
# define KEY_W			13
# define KEY_LEFT		123
# define KEY_RIGHT		124
# define KEY_ESC		53

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
}				t_img;

// Vector2D
typedef struct	s_vec {
	double		x;
	double		y;
} t_vec;

// Ray 2D
typedef struct	s_ray {
	t_vec		pos;  // レイの始点の位置ベクトル
	t_vec		way;  // レイの始点から伸びる方向ベクトル
} t_ray;

// Player
typedef struct	s_player {
	t_vec		pos;  // 現在位置(px)[x, y]
	t_vec		dir;       // 現在向いている方向のベクトル
	t_vec		plane;     // 2Dレイキャスティング用のカメラ平面
	int			is_moving; // 動くキーが押されているか (W=1, S=-1, None=0)
	int			is_sidling;  // 動くキーが押されているか (D=1, A=-1, None=0)
	int			is_rotating; // 動くキーが押されているか (左矢印=1, 右矢印=-1, None=0)
}				t_player;

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
	double		height_base;

	double		*z_buffer;
} t_game;

/* errors.c */
int return_error_msg(char *msg);
void put_err_msg(char *msg);
/* game.c */
int init_game(t_game *game);
/* read_cub.c */
int read_cub(t_game *game, char *path);

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
