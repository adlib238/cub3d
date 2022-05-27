/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 18:22:25 by kfumiya           #+#    #+#             */
/*   Updated: 2022/05/27 10:45:26 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	main(int ac, char **av)
{
	t_game	game;
	int		save;

	save = (ac == 3 && !ft_strcmp(av[1], "--save"));
	if (ac < (2 + save))
		put_err_msg("No map spexified");
	if (init_game(&game) == ERROR || read_cub(&game, av[1]) == ERROR)
	{
		put_err_msg("cub file could not be read");
		exit(EXIT_FAILURE);
	}
	set_screen(&game, save);
	// mlx_hook(game.win, 2, 1L << 0, &key_press, &game);
	// mlx_hook(game.win, 3, 1L << 1, &key_release, &game);
	// mlx_hook(game.win, 17, 0, &close_window, &game);
	// mlx_loop_hook(game.mlx, &main_loop, &game);
	// mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}
