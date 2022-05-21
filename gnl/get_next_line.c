/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 00:10:20 by kfumiya           #+#    #+#             */
/*   Updated: 2021/01/02 20:32:26 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		find_nl(char *save)
{
	size_t	i;

	i = 0;
	if (!save)
		return (0);
	while (save[i] != '\0')
	{
		if (save[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*write_line(char *save)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!save)
		return (NULL);
	while (save[i] != '\0' && save[i] != '\n')
		i++;
	if (!(str = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (save[i] != '\0' && save[i] != '\n')
	{
		str[i] = save[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*save_line(char *save)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!save)
		return (NULL);
	while (save[i] != '\0' && save[i] != '\n')
		i++;
	if (save[i] == '\0')
	{
		free_null(save);
		return (NULL);
	}
	if (!(str = (char *)malloc(sizeof(char) * (ft_strlen(save) - i + 1))))
		return (NULL);
	i++;
	while (save[i] != '\0')
		str[j++] = save[i++];
	str[j] = '\0';
	free_null(save);
	return (str);
}

int		free_null(void *ptr)
{
	free(ptr);
	ptr = NULL;
	return (0);
}

int		get_next_line(int fd, char **line)
{
	int			r;
	char		*buf;
	static char *save[FD_MAX];

	r = 1;
	if (fd < 0 || !line || BUFFER_SIZE <= 0 || fd > FD_MAX)
		return (-1);
	if (!(buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while (!(find_nl(save[fd])) && r)
	{
		if ((r = read(fd, buf, BUFFER_SIZE)) == -1)
			return (free_null(buf) | -1);
		buf[r] = '\0';
		if (!(save[fd] = gnl_strjoin(save[fd], buf)))
			return (free_null(buf) | -1);
	}
	free_null(buf);
	*line = write_line(save[fd]);
	save[fd] = save_line(save[fd]);
	if (!r)
		return (0);
	if (!(*line) || !(save[fd]))
		return (-1);
	return (1);
}
