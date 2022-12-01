/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 21:04:32 by mmasubuc          #+#    #+#             */
/*   Updated: 2021/12/11 17:50:38 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	bgn_set(char *str, char *set)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(set, str[i]) == NULL)
			break ;
		i++;
	}
	return (i);
}

static int	end_set(char *str, char *set)
{
	int	size;

	size = ft_strlen(str);
	while (size >= 0)
	{
		if (ft_strrchr(set, str[size]) == NULL)
			break ;
		size--;
	}
	return (size);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		len;
	int		bgn;
	int		end;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return ((char *)s1);
	len = ft_strlen(s1);
	bgn = bgn_set((char *)s1, (char *)set);
	if (bgn == len)
		return (str = ft_calloc(1, 1));
	end = end_set((char *)s1, (char *)set);
	str = ft_substr(s1, bgn, (end - bgn + 1));
	if (str == NULL)
		return (NULL);
	return (str);
}
