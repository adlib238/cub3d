/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:07:27 by mmasubuc          #+#    #+#             */
/*   Updated: 2022/06/12 22:36:07 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	get_max_value(size_t x, size_t y)
{
	if (x >= y)
		return (x);
	else
		return (y);
}

char	*ft_strjoin_new_line(char const *s1, char const *s2)
{
	char	*newstr;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	newstr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (newstr == NULL)
		return (NULL);
	while (s1[i] != '\0' && s1[i] != '\n')
	{
		newstr[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0' && s2[j] != '\n')
	{
		newstr[i] = s2[j];
		i++;
		j++;
	}
	newstr[i] = '\0';
	return (newstr);
}

char	*ft_strchr_return_next_char(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i + 1]);
		i++;
	}
	return (NULL);
}

size_t	skip_spaces(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ')
			break ;
		i++;
	}
	return (i);
}

char	**make_copy_map(t_data *data)
{
	char	**map_dup;
	size_t	i;

	map_dup = (char **)malloc(sizeof(char *) * (data->cubfile->map_row + 1));
	if (!map_dup)
		return (NULL);
	i = 0;
	while (i < data->cubfile->map_row)
	{
		map_dup[i] = ft_strdup(data->cubfile->map[i]);
		if (!map_dup)
			return (NULL);
		i++;
	}
	map_dup[i] = NULL;
	return (map_dup);
}
