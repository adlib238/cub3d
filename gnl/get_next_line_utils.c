/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 00:10:00 by kfumiya           #+#    #+#             */
/*   Updated: 2021/04/13 19:50:29 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	*ft_memmove(void *s1, const void *s2, size_t len)
{
	unsigned char	*dst;
	unsigned char	*src;

	dst = (unsigned char *)s1;
	src = (unsigned char *)s2;
	if (!src && !dst)
		return (NULL);
	if (src < dst)
	{
		while (len--)
			*(dst + len) = *(src + len);
	}
	else
	{
		while (len--)
		{
			*(dst++) = *(src++);
		}
	}
	return ((void *)dst);
}

char	*gnl_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	s1_len;
	size_t	s2_len;
	size_t	total_len;

	if (!s1 && !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	total_len = s1_len + s2_len;
	if (!(str = (char *)malloc(sizeof(*str) * (total_len + 1))))
		return (NULL);
	ft_memmove(str, s1, s1_len);
	ft_memmove(str + s1_len, s2, s2_len);
	str[total_len] = '\0';
	free_null((char *)s1);
	return (str);
}
