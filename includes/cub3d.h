/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:39:08 by mmasubuc          #+#    #+#             */
/*   Updated: 2022/06/17 12:20:07 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdint.h>
# include <math.h>
# include <stdlib.h>
# include <stdbool.h>
# include "../mlx/mlx.h"
# include "../mlx/mlx_int.h"
# include "../libft/libft.h"

# define ERROR	-1
# define RGB_MAX 16777215
# define MAX_MAP_W 200
# define MAX_MAP_H 200
# define MOVE_P (0.033)

# define KEY_A			97
# define KEY_S			115
# define KEY_D			100
# define KEY_W			119
# define KEY_LEFT		65361
# define KEY_RIGHT		65363
# define KEY_ESC		65307
# define KEY_Q			113

# define NB_TYPE 6
# define INVALID_ARG "Invalid arguments"
# define MLX_INIT_FAIL "Mlx initialization failed"
# define MLX_NEW_WINDOW_FAIL "Mlx window creation failed"
# define XPM_TO_IMG_FAIL "Xpm to image conversion failed"
# define MALLOC_FAIL "Malloc failed"
# define OPEN_FAIL "Open failed"
# define READ_FAIL "Read failed"
# define CLOSE_FAIL "Close failed"
# define INVALID_CUBFILE "Invalid cubfile"
# define INVALID_MAP "Invalid map"

typedef enum e_type
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	ALL_DIRECTION,
	FLOOR = 0,
	CEILING,
}			t_type;

typedef struct s_vec2
{
	double		x;
	double		y;
}	t_vec2;

typedef struct s_cubfile
{
	void		*textures[4];
	uint32_t	colors[2];
	size_t		map_row;
	size_t		map_col;
	char		**map;
}	t_cubfile;

typedef struct s_image {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}	t_image;

typedef struct s_player {
	t_vec2	pos;
	t_vec2	dir;
	t_vec2	plane;
	int		is_moving;
	int		is_sidling;
	int		is_rotating;
	t_type	direction;
}	t_player;

typedef struct s_data
{
	void		*mlx;
	t_cubfile	*cubfile;
	void		*win;
	t_player	player;
	t_image		img;
	int			screen_width;
	int			screen_height;
	double		horizon;
	t_image		tex_n;
	t_image		tex_s;
	t_image		tex_w;
	t_image		tex_e;
	int			tex_width;
	int			tex_height;
}	t_data;

typedef struct s_ray {
	double		camera_x;
	t_vec2		dir;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		perp_wall_dist;
	int			side;
	int			step_x;
	int			step_y;
	double		delta_dist_x;
	double		delta_dist_y;
	t_image		*tex;
	u_int32_t	color;
}	t_ray;

typedef struct s_wall
{
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		wall_x;
	int			texture_x;
	double		step;
	double		texture_pos_y;
	int			texture_y;
}	t_wall;

// validation.c
void		is_valid_argv(int argc, char **argv);
bool		is_extension(char *arg, int i);

// init.c
void		init_data(t_data *data);
void		init_mlx(t_data *data);

// utils.c
size_t		get_max_value(size_t x, size_t y);
char		*ft_strjoin_new_line(char const *s1, char const *s2);
char		*ft_strchr_return_next_char(const char *s, int c);
size_t		skip_spaces(char *line);
char		**make_copy_map(t_data *data);

// free.c
void		free_2d_array(char **content);
void		free_buf(void **buf);
void		free_mlx(t_data *data, t_type type);
void		free_data(t_data *data);

// exit.c
void		exit_program(char *msg, t_data *data, t_type type);
int			close_window(t_data *data);

/* draw_wall.c */
void		draw_wall(t_data *data);
/* errors.c */
int			return_error_msg(char *msg);
void		put_err_msg(char *msg);
/* game.c */
void		set_screen(t_data *data);
int			main_loop(t_data *data);
/* init_player.c */
void		init_player(t_player *player, char dir);
/* mlx_utils.c */
void		my_mlx_pixel_put(t_image *img, int x, int y, int color);
int			read_image(t_data *data, t_image *img, char *filepath);
u_int32_t	get_color_pix(t_image img, int x, int y);
/* set_data.c */
void		set_data(t_data *data);
void		set_tex(t_data *data);
/* vector.c */
double		vec_length(t_vec2 vec);
double		deg_rad(int x);
void		vec_rotate(t_vec2 *vec, double rad);
/* wall_utils.c */
void		set_wall_color(t_data *data, t_ray *ray);
void		set_texture(t_data *data, t_ray *ray);
/* debug_ray.c */
void		print_ray(t_ray ray);
void		print_wall(t_wall wall);
/* debug.c */
void		print_map(t_data *data);
void		print_da(t_data *data);
void		print_image(t_data *data);
void		print_info(t_data *data);
/* player.c */
void		update_player(t_data *data);
/* hook.c */
int			exit_window(t_data *data);
int			key_press(int keycode, t_data *data);
int			key_release(int keycode, t_data *data);
/* math_utils.c */
int			max(int a, int b);
int			min(int a, int b);

#endif
