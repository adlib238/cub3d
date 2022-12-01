/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 21:04:24 by mmasubuc          #+#    #+#             */
/*   Updated: 2020/11/28 05:07:15 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	size_t		j;
	const char	*tmp;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0' && len > 0)
	{
		if (haystack[i] == *needle)
		{
			tmp = &haystack[i];
			j = 0;
			while (tmp[j] == needle[j] && j < len)
			{
				if (needle[j + 1] == '\0')
					return ((char *)tmp);
				j++;
			}
		}
		len--;
		i++;
	}
	return (NULL);
}
