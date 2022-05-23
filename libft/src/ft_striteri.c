/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:55:18 by kfumiya           #+#    #+#             */
/*   Updated: 2022/05/23 12:55:24 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char*s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (s == NULL)
		return ;
	i = 0;
	while (*(s + i))
	{
		f(i, (s + i));
		i++;
	}
}
