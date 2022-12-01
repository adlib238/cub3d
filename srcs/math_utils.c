/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 10:03:48 by kfumiya           #+#    #+#             */
/*   Updated: 2022/06/15 10:08:59 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

int
	min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}
