/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 19:17:30 by kfumiya           #+#    #+#             */
/*   Updated: 2021/06/06 06:51:22 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	test(t_game *game)
{
	printf("\n\n");
	printf("test........ok!\n");
	printf("---game-------------------------------------\n");
	printf("sp_count: %d\n", game->sp_count);
	printf("options: %d\n", game->options);


	printf("----------sprites--------------------\n");
	t_sprite *tmp;
	tmp = game->sprites;
	while (tmp)
	{
		printf("pos_x: %lf pos_y: %lf\n", tmp->pos.x, tmp->pos.y);
		printf("distance: %lf\n", tmp->distance);
		printf("tex_path: %s\n", tmp->tex_path);
		tmp = tmp->next;
		printf("\n");
	}
	printf("\n\n\n\n");

	printf("---config-------------------------------------\n");
	printf("requested_width  : %d\n", game->config.requested_width);
	printf("requested_height : %d\n", game->config.requested_height);
	for (int i = 0; i < game->config.rows; i++)
	{
		for (int j = 0; j < game->config.columns; j++)
			printf("%d", game->config.map[i][j]);
		printf("\n");
	}
	printf("rows : %d\n", game->config.rows);
	printf("columns : %d\n", game->config.columns);
	for (int i = 0; i < TEXTURES; i++)
	{
		printf("tex_path[%s]\n", game->config.tex_path[i]);
	}
	printf("floor_color: %d\n", game->config.c[TEX_FLOOR]);
	printf("ciling_color: %d\n", game->config.c[TEX_CEILING]);
	for (int i = 0; i < C_LAST; i++)
	{
		printf("set[%d] = %d\n", i, game->config.set[i]);
	}
	printf("pl_x : %d\n", game->config.pl_x);
	printf("pl_y : %d\n", game->config.pl_y);
	printf("pl_dir : %c\n", game->config.pl_dir);
	printf("pl_pos: %d\n", game->config.pl_pos);
	// printf("fov: %f\n", game->config.fov);
	// printf("rotate_speed : %f\n", game->config.rotate_speed);
	// printf("move_speed : %f\n", game->config.move_speed);
	printf("\n\n\n\n");


	printf("---window-------------------------------\n");
	// printf("ptr: %p\n", game->window.ptr);
	// printf("win: %p\n", game->window.win);
	printf("size_x : %f\nsize_y : %f\n", game->window.size.x, game->window.size.y);
	printf("\n\n\n\n");




	// printf("---camera-------------------------------\n");
	// printf("pos_x: %f\npos_y: %f\n", game->camera.pos.x, game->camera.pos.y);
	// printf("dir_x: %f\ndir_y: %f\n", game->camera.dir.x, game->camera.dir.y);
	// printf("x_dir_x: %f\nx_dir_y: %f\n", game->camera.x_dir.x, game->camera.x_dir.y);
	// printf("plane_x: %f\nplane_y: %f\n", game->camera.plane.x, game->camera.plane.y);
	// printf("\n\n\n\n");
	

	// printf("---image--------------------------------\n");
	// printf("img: %p\n", game->window.screen.img);
	// printf("ptr: %p\n", game->window.screen.ptr);
	// printf("bpp: %d\n", game->window.screen.bpp);
	// printf("size_line: %d\n", game->window.screen.size_line);
	// printf("endian: %d\n", game->window.screen.endian);
	// printf("\n\n\n\n");

	// printf("---sprites------------------------------\n");
	// printf("sprites_count: %d\n", game->sp_count);
	// while (game->sprites)
	// {
	// 	printf("---tex_path: %s---------\n", game->sprites->tex_path);
	// 	printf("pos_x: %f\npos_y: %f\n", game->sprites->pos.x, game->sprites->pos.y);
	// 	printf("distance: %f\n", game->sprites->distance);
	// 	printf("---tex------\n");
	// 	printf("path: %s\n", game->sprites->tex->path);
	// 	printf("tex: %p\n", game->sprites->tex->tex);
	// 	printf("ptr: %p\n", game->sprites->tex->ptr);
	// 	printf("pos_x: %f\npos_y: %f\n", game->sprites->tex->start.x, game->sprites->tex->start.y);
	// 	printf("pos_x: %f\npos_y: %f\n", game->sprites->tex->end.x, game->sprites->tex->end.y);
	// 	printf("width: %d\n", game->sprites->tex->width);
	// 	printf("height: %d\n", game->sprites->tex->height);
	// 	printf("bpp: %d\n", game->sprites->tex->bpp);
	// 	printf("size_line: %d\n", game->sprites->tex->size_line);
	// 	printf("endian: %d\n", game->sprites->tex->endian);
	// 	printf("\n\n");
	// 	game->sprites = game->sprites->next;
	// }
	// printf("\n\n\n\n");

	// printf("---tex---------------------------------------\n");
	// for (int i = 0; i < TEXTURES-2; i++)
	// {
	// 	if (game->tex[i].ptr)
	// 	{
	// 		printf("path: %s\n", game->tex[i].path);
	// 		printf("tex: %p\n", game->tex[i].tex);
	// 		printf("ptr: %p\n", game->tex[i].ptr);
	// 		printf("pos_x: %f\npos_y: %f\n", game->tex[i].start.x, game->tex[i].start.y);
	// 		printf("pos_x: %f\npos_y: %f\n", game->tex[i].end.x, game->tex[i].end.y);
	// 		printf("width: %d\n", game->tex[i].width);
	// 		printf("height: %d\n", game->tex[i].height);
	// 		printf("bpp: %d\n", game->tex[i].bpp);
	// 		printf("size_line: %d\n", game->tex[i].size_line);
	// 		printf("endian: %d\n", game->tex[i].endian);
	// 		printf("\n\n");
	// 	}
	// }
	// printf("\n\n\n\n");

	// printf("---game-----------------------------------------\n");
	// printf("move_x: %f\nmove_y: %f\n", game->move.x, game->move.y);
	// printf("x_move_x: %f\nx_move_y: %f\n", game->x_move.x, game->x_move.y);
	// printf("rotate_x: %f\nrotate_y: %f\n", game->rotate.x, game->rotate.y);
	// printf("sp_count: %d\n", game->sp_count);
	// printf("options: %d\n", game->options);
	// // printf("camera_x: ");
	// // printf("depth: ");
	// // printf("sf_dist: ");
	// printf("cos[0]: %f\ncos[1]: %f\n", game->cos[0], game->cos[1]);
	// printf("sin[0]: %f\nsin[1]: %f\n", game->sin[0], game->sin[1]);


	return (0);
}
