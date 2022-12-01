/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:39:32 by mmasubuc          #+#    #+#             */
/*   Updated: 2022/06/17 12:02:19 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	is_valid_argv(argc, argv);
	init_data(&data);
	parse_cubfile(&data, argv[1]);
	set_screen(&data);
	mlx_hook(data.win, KeyPress, KeyPressMask, key_press, &data);
	mlx_hook(data.win, KeyRelease, KeyReleaseMask, key_release, &data);
	mlx_hook(data.win, ClientMessage, 1L << 17, close_window, &data);
	mlx_loop_hook(data.mlx, &main_loop, &data);
	mlx_loop(data.mlx);
	free_mlx(&data, ALL_DIRECTION);
	free_data(&data);
	return (0);
}
