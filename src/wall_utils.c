/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 13:05:47 by kfumiya           #+#    #+#             */
/*   Updated: 2022/05/26 13:06:14 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	set_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			ray->tex = &game->tex_w;
		else
			ray->tex = &game->tex_e;
	}
	else
	{
		if (ray->step_y > 0)
			ray->tex = &game->tex_n;
		else
			ray->tex = &game->tex_s;
	}
}
