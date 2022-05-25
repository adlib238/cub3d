/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 21:30:12 by kfumiya           #+#    #+#             */
/*   Updated: 2022/05/24 13:08:03 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int
// 	exit_game(t_game *game, int code)
// {
// 	clear_config(&game->config);
// 	clear_window(&game->window);
// 	clear_textures(game);
// 	clear_sprites(&game->sprites);
// 	free(&game->buf);
// 	exit(code);
// 	return (code);
// }

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
	// game->tex_width = 0;
	// game->tex_height = 0;
	game->sky_color = UINT32_MAX;
	game->ground_color = UINT32_MAX;
	game->height_base = 0;
	return (0);
}

// static int
// 	buf_malloc(t_game *game)
// {
// 	t_window *win;
// 	int i;
// 	int	j;
// 	int	**buf;

// 	win = &game->window;
// 	if (!(buf = (int **)malloc(sizeof(int *) * win->size.y)))
// 		return (0);
// 	i = 0;
// 	while (i < win->size.y)
// 	{
// 		if (!(buf[i] = malloc(sizeof(int) * win->size.x)))
// 			return (0);
// 		j = 0;
// 		while (j < win->size.x)
// 		{
// 			buf[i][j] = 0;
// 			j++;
// 		}
// 		i++;
// 	}
// 	// printf("buf_width: %d\nbuf_height: %d\n", i, j);
// 	game->buf = buf;
// 	return (1);
// }

// int
// 	start_game(t_game *game)
// {
// 	if (!init_window(&game->window, &game->config))
// 		return (put_error("Error:\nmlx failed to create window or image.\n",
// 							game));
// 	// set_start_pos(&game->config, &game->camera);
// 	// set_start_angle(&game->config, &game->camera);
// 	if (!load_textures(game))
// 		return (put_error("Error:\nfailed to load textures.\n", game));
// 	if (!buf_malloc(game))
// 		return (put_error("Error:\nbuf malloc miss.", game));
// 	set_pos(&game->pos, game->config.pl_x, game->config.pl_y);
// 	// make_tables(game);
// 	return (1);
// }

// int
// 	screenshot(t_game *game)
// {
// 	update_screen(game);
// 	return (exit_game(game, EXIT_SUCCESS));
// 	// update_window(game);
// 	// if (!save_bmp(game))
// 	// 	put_error("Error:\nFailed to save screenshot.");
// 	return (exit_game(game, EXIT_SUCCESS));
// }
