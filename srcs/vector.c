/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 10:30:25 by kfumiya           #+#    #+#             */
/*   Updated: 2022/06/15 10:18:43 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double
	vec_length(t_vec2 vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y));
}

double
	deg_rad(int x)
{
	return ((double)x / 180 * M_PI);
}

void
	vec_rotate(t_vec2 *vec, double rad)
{
	t_vec2	old_vec;

	old_vec = *vec;
	vec->x = old_vec.x * cos(rad) - old_vec.y * sin(rad);
	vec->y = old_vec.x * sin(rad) + old_vec.y * cos(rad);
}
