/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 09:54:30 by kfumiya           #+#    #+#             */
/*   Updated: 2022/05/24 10:02:05 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	set_free(void **dst, void *src)
{
	free(*dst);
	*dst = src;
}

void
	instant_free(void **strs)
{
	int	i;

	i = -1;
	while (strs[++i])
		set_free((void **)&strs[i], NULL);
	set_free((void **)&strs, NULL);
}