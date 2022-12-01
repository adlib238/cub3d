/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 21:03:46 by mmasubuc          #+#    #+#             */
/*   Updated: 2022/06/14 22:54:07 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"

static size_t	get_size_of_array(char const *s, char c)
{
	size_t	i;
	size_t	size;
	bool	counted;

	i = 0;
	size = 0;
	counted = false;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			if (!counted)
			{
				size++;
				counted = true;
			}
		}
		else
		{
			if (counted)
				counted = false;
		}
		i++;
	}
	return (size);
}

int	count_substr_len(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			break ;
		i++;
	}
	return (i);
}

static bool	malloc_error(char **ary, size_t ary_nb)
{
	size_t	i;

	i = 0;
	if (ary[ary_nb])
		return (false);
	while (i < ary_nb)
	{
		free(ary[i]);
		i++;
	}
	free(ary);
	return (true);
}

bool	split_lines(char **array, char const *line, char c, int size)
{
	int	j;
	int	cnt;
	int	start;

	j = 0;
	cnt = 0;
	start = 0;
	while (j < size)
	{
		cnt = count_substr_len(&line[start], c);
		if (cnt > 0)
		{
			array[j] = ft_substr(line, start, cnt);
			if (malloc_error(array, j++))
				return (false);
			start += cnt;
		}
		else
			start += 1;
	}
	array[j] = NULL;
	return (true);
}

char	**ft_split(char const *s, char c)
{
	int		size;
	char	**array;

	if (s == NULL)
		return (NULL);
	size = get_size_of_array(s, c);
	array = (char **)malloc(sizeof(char *) * (size + 1));
	if (!array)
		return (NULL);
	if (!split_lines(array, s, c, size))
		return (NULL);
	return (array);
}
