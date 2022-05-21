/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 22:14:23 by kfumiya           #+#    #+#             */
/*   Updated: 2021/06/06 05:38:08 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void
	set_pos(t_pos *pos, double x, double y)
{
	pos->x = x;
	pos->y = y;
}

void
	copy_pos(t_pos *pos, t_pos *org)
{
	pos->x = org->x;
	pos->y = org->y;
}

void
	set_pos_fl(t_pos_fl *pos, float x, float y)
{
	pos->x = x;
	pos->y = y;
}

void
	copy_pos_fl(t_pos_fl *pos, t_pos_fl *org)
{
	pos->x = org->x;
	pos->y = org->y;
}
