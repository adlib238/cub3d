/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 19:24:35 by kfumiya           #+#    #+#             */
/*   Updated: 2021/04/13 19:24:37 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int
	ft_write_int(char *buf, int val, int start)
{
	int	length;
	int	tmp;

	length = 1;
	tmp = val;
	while (tmp > 9)
	{
		length++;
		tmp /= 10;
	}
	if (val == 0)
		buf[start++] = '0';
	else
	{
		tmp = length;
		while (val > 0)
		{
			buf[start + --tmp] = "0123456789"[val % 10];
			val /= 10;
		}
		start += length;
	}
	buf[start] = 0;
	return (start);
}

int
	ft_write_str(char *buf, char *str, int start)
{
	int	i;

	i = 0;
	while (str[i])
		buf[start++] = str[i++];
	buf[start] = 0;
	return (start);
}
