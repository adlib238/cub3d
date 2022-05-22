/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 11:10:53 by kfumiya           #+#    #+#             */
/*   Updated: 2022/05/22 11:21:31 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
static void	brainless_free(char	**str)
{
	free(*str);
	*str = NULL;
}

static size_t	check_n(char	*s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	return (i);
}

static char	*get_line(char	*save_chr, char	**save)
{
	char	*tmp;
	char	*line;

	line = ft_substr(*save, 0, check_n(*save) + 1);
	if (line == NULL)
		return (NULL);
	tmp = ft_substr(*save, check_n(*save) + 1, ft_strlen(save_chr + 1));
	if (tmp == NULL)
	{
		brainless_free(&line);
		return (NULL);
	}
	brainless_free(save);
	*save = tmp;
	return (line);
}

static char	*join_line(int	fd, int	*read_size, char	**save, char	**buf)
{
	char	*save_chr;
	char	*tmp;

	while (*read_size > 0)
	{
		save_chr = ft_strchr(*save, '\n');
		if (save_chr != NULL)
			return (get_line(save_chr, save));
		else
		{
			*read_size = read(fd, *buf, BUFFER_SIZE);
			if (*read_size == -1)
				return (NULL);
			(*buf)[*read_size] = '\0';
			tmp = ft_join(*save, *buf);
			if (tmp == NULL)
				return (NULL);
			brainless_free(save);
			*save = tmp;
		}
	}
	return (no_newline(save));
}

char	*get_next_line(int	fd)
{
	static char	*save[OPEN_MAX];
	char		*buf;			
	char		*line;			
	int			read_size;

	if (fd < 0 || BUFFER_SIZE < 1 || OPEN_MAX < fd)
		return (NULL);
	buf = (char *)malloc((size_t)BUFFER_SIZE + 1);
	if (buf == NULL)
		return (NULL);
	if (save[fd] == NULL)
		save[fd] = ft_substr("", 0, 0);
	if (save == NULL)
		return (NULL);
	read_size = 1;
	line = join_line(fd, &read_size, &save[fd], &buf);
	brainless_free(&buf);
	if (line == NULL || read_size == -1 || read_size == 0)
	{
		brainless_free(&save[fd]);
		if (read_size == -1 || line == NULL)
			return (NULL);
	}
	return (line);
}
