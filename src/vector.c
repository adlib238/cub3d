/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:01:45 by kfumiya           #+#    #+#             */
/*   Updated: 2022/05/27 10:42:48 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double
	vec_length(t_vec vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y));
}

double
	deg_rad(int x)
{
	return ((double)x / 180 * M_PI);
}

void
	vec_rotate(t_vec *vec, double rad)
{
	t_vec	old_vec;

	old_vec = *vec;
	vec->x = old_vec.x * cos(rad) + old_vec.y * sin(rad);
	vec->y = old_vec.x * sin(rad) + old_vec.y * cos(rad);
}
