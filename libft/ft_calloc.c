/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 20:59:21 by mmasubuc          #+#    #+#             */
/*   Updated: 2021/12/11 17:52:48 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned long	i;
	unsigned char	*ptr;

	i = 0;
	ptr = malloc(count * size);
	if (ptr == 0)
		return (ptr);
	while (count * size - i > 0)
	{
		ptr[i] = '\0';
		i++;
	}
	return ((void *)ptr);
}
