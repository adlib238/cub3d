/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 18:22:25 by kfumiya           #+#    #+#             */
/*   Updated: 2022/05/24 09:26:14 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	main(int ac, char **av)
{
	t_game game;
	int save;
	(void)ac;

	save = (ac == 3 && !ft_strcmp(av[1], "--save"));
	if (ac < (2 + save))
		put_err_msg("No map spexified");
	if (init_game(&game) == ERROR || read_cub(&game, av[1]) == ERROR)
	{
		put_err_msg("cub file could not be read");
		exit(EXIT_FAILURE);
	}
	// if (!parse_config(&game, av[1 + save]))
	// 	return (put_error("Error:\nSet config error.\n", &game));
	// if (!start_game(&game))
	// 	return (EXIT_FAILURE);
	// if (game.options)
	// 	return (screenshot(&game));
	// mlx_hook(game.window.win, X_EVENT_KEY_PRESS, 0, &key_press, &game);
	// mlx_hook(game.window.win, X_EVENT_KEY_RELEASE, 0, &key_release, &game);
	// mlx_hook(game.window.win, X_EVENT_EXIT, 0, &exit_hook, &game);
	// mlx_loop_hook(game.window.ptr, &main_loop, &game);
	// mlx_loop(game.window.ptr);
	// test(&game);
	return (EXIT_SUCCESS);
}
