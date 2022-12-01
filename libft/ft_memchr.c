/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 21:00:24 by mmasubuc          #+#    #+#             */
/*   Updated: 2021/12/11 18:09:05 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	chara;
	unsigned char	*str;
	size_t			i;

	chara = (unsigned char)c;
	str = (unsigned char *)s;
	i = 0;
	while (n-- > 0)
	{
		if (str[i] == chara)
			return (&str[i]);
		i++;
	}
	return (NULL);
}
