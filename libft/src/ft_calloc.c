/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 10:03:19 by kfumiya           #+#    #+#             */
/*   Updated: 2022/05/23 12:58:46 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;
	size_t			i;

	if (size > 0 && (SIZE_MAX / size < count))
		return (NULL);
	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < count * size)
		*(ptr + i++) = 0;
	return (ptr);
}

