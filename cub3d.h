/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 18:25:53 by kfumiya           #+#    #+#             */
/*   Updated: 2021/06/06 08:16:26 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "gnl/get_next_line.h"
# include "utils/utils.h"
# include "mlx.h"

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

// typedef struct	s_ray
// {
// 	int			column;
// 	int			row;
// 	double		distance;
// 	int			direction;
// 	int			side;
// 	int			height;
// 	t_pos		ray_pos;
// 	t_pos		ray_dir;
// 	t_pos		map_pos;
// 	t_pos		side_dist;
// 	t_pos		delta_dist;
// 	t_pos		step;
// 	double		wall_x;
// 	t_pos		floor_wall;
// 	t_pos		c_floor;
// }				t_ray;

// typedef struct s_w_ray
// {
// 	double camerax;
// 	t_pos raydir;
// 	t_pos map;//int
// 	t_pos sidedist;
// 	t_pos deltadist;
// 	double p_walldist;
// 	t_pos step;//int
// 	int lineheight;
// 	int drawstart;
// 	int drawend;
// 	int texnum;
// 	double wallx;
// 	t_pos tex_pos;
// 	t_pos floorx_wall;
// 	double weight;
// 	t_pos currentfloor;
// 	t_pos floortex;//int
// } t_w_ray;

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

typedef struct	s_image
{
	void	*img;
	void	*ptr;
	int		bpp;
	int		size_line;
	int		endian;
}	t_image;

typedef struct s_window
{
	void		*ptr;
	void		*win;
	t_image		screen;
	t_pos		size;
} t_window;

// typedef struct	s_camera
// {
// 	t_pos	pos;
// 	t_pos	dir;
// 	t_pos	x_dir;
// 	t_pos	plane;
// }				t_camera;

typedef struct	s_tex
{
	char	*path;
	void	*tex;
	void	*ptr;
	t_pos	start;
	t_pos	end;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}				t_tex;

typedef struct	s_sprite_draw
{
	int			sprite_screen;
	t_pos		pos;
	t_pos		transform;
	t_pos		spr_s;
	t_pos		draw_x;
	t_pos		draw_y;
	t_pos		tex_pos;
	int			fact;
	int			draw_y_org;
}				t_sprite_draw;

typedef struct s_sprite
{
	t_pos			pos;
	double			distance;
	char			*tex_path;
	t_tex			*tex;
	struct s_sprite	*next;
	struct s_sprite	*sorted;
} t_sprite;

typedef struct s_config
{
	int				requested_height;
	int				requested_width;
	int				**map;
	int				rows;
	int				columns;
	char			*tex_path[TEXTURES];
	unsigned int	c[TEXTURES];
	int				set[C_LAST];
	int				pl_x;
	int				pl_y;
	char			pl_dir;
	int				pl_pos;
} t_config;

typedef struct s_game
{
	t_config	config;
	// t_camera	camera;
	t_window	window;
	t_sprite	*sprites;
	t_tex		tex[TEXTURES];
	int sp_count;
	int options;
	int **buf;
	t_pos pos;
	t_pos dir;
	t_pos plane;
	double movespeed;
	double rotspeed;
	// t_pos		move;
	// t_pos		x_move;
	// t_pos		rotate;
	// double		camera_x[1920];
	// double		depth[1920];
	// double		sf_dist[1080];
	// double		cos[2];
	// double		sin[2];
} t_game;

int test(t_game *game);

void init_game(t_game *game, int save);

int exit_game(t_game *game, int code);

int put_error(char *message, t_game *game);

int	out_error(char *message);

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

// void set_start_pos(t_config *config, t_camera *camera);

// void set_start_angle(t_config *config, t_camera *camera);

// void make_tables(t_game *game);

// int screenshot(t_game *game);

// void update_screen(t_game *game);

// int draw_rectangle(t_window *window, t_pos *p1, t_pos *p2, int color);

// void	draw_pixel(t_window *w, t_pos *pos, int color);

// void raycast(t_game *game, t_ray *ray, int column);

// void draw_wall(t_game *game, t_ray *ray);

// void draw_ceiling_floor(t_game *game, t_ray *ray);

// int move_camera(t_game *game, int direction);

// int move_perp_camera(t_game *game, int direction);

// int rotate_camera(t_game *game, int dir);

int key_press(int keycode, t_game *game);

int key_release(int keycode, t_game *game);

int exit_hook(t_game *game);

int main_loop(t_game *game);

// void update_window(t_game *game);

// int distance_shade(int options, int color, double distance);

// int shade_color(int color, double divide);

// int draw_vertical_line(t_window *window, t_pos *start,
// 								int length, int color);

#endif
