/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 10:50:06 by kfumiya           #+#    #+#             */
/*   Updated: 2022/05/25 10:56:53 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	print_config(t_game *game)
{
	printf("\n=== config info ==============================\n");
	printf("screen_height: %d\n", game->screen_height);
	printf("screen_width: %d\n", game->screen_width);
	printf("ground_color: %d\n", game->ground_color);
	printf("sky_color: %d\n", game->sky_color);
	printf("tex_n.img: %p\n", game->tex_n.img);
	printf("tex_s.img: %p\n", game->tex_s.img);
	printf("tex_w.img: %p\n", game->tex_w.img);
	printf("tex_e.img: %p\n", game->tex_e.img);
	printf("\n---INPUT MAP------------------------\n");
	for (int i = 0; i < game->map_row; i++)
		printf("%s\n", game->map[i]);
	printf("==============================================\n");
}
