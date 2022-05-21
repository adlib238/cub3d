/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 19:34:15 by kfumiya           #+#    #+#             */
/*   Updated: 2021/04/21 17:46:03 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	out_error(char *message)
{
	write(2, message, ft_strlen(message));
	return (0);
}

int
	put_error(char *message, t_game *game)
{
	int i;

	i = 0;
	write(2, message, ft_strlen(message));
	return (exit_game(game, EXIT_SUCCESS));
}