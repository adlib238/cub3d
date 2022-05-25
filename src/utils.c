/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 10:22:23 by kfumiya           #+#    #+#             */
/*   Updated: 2022/05/24 14:29:57 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool
	str_isvalid_set(char *str, int(*f)(int))
{
	int	i;

	if (!str)
		return (false);
	i = 0;
	while (str[i])
	{
		if (!f(str[i]))
			return (false);
		i++;
	}
	return (true);
}

int
	strs_size(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}
