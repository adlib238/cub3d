/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_resolution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 10:05:51 by kfumiya           #+#    #+#             */
/*   Updated: 2022/05/25 09:45:18 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	set_resolution(t_game *game, char *w, char *h)
{
	int width;
	int height;

	if (game->screen_width || game->screen_height)
		return (return_error_msg("The resolution is already set"));
	if (!str_isvalid_set(w, ft_isdigit) || !str_isvalid_set(h, ft_isdigit))
		return (return_error_msg("____Resolution is invalid"));
	width = ft_atoi(w);
	height = ft_atoi(h);
	if (width < 1 || height < 1)
		return (return_error_msg("Resolution is invalid________"));
	game->screen_width = 0;
	game->screen_height = 0;
	return (0);
}