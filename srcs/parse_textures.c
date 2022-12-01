/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:51:45 by mmasubuc          #+#    #+#             */
/*   Updated: 2022/06/16 20:11:52 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"

bool	parse_textures(t_data *data, char *line, int i)
{
	size_t	start;

	if (data->cubfile->textures[i] || line[2] == '\0')
		return (false);
	else
	{
		start = 2 + skip_spaces(&line[2]);
		if (ft_strlen(&line[start]) == 0)
			return (false);
		data->cubfile->textures[i]
			= ft_substr(line, start, ft_strlen(line) - start);
		if (!data->cubfile->textures[i])
			exit_program(MALLOC_FAIL, data, 0);
		if (!is_unique_texture(data, i))
			return (false);
	}
	return (true);
}

bool	is_unique_texture(t_data *data, int i)
{
	int		j;
	size_t	len;

	j = 0;
	len = ft_strlen(data->cubfile->textures[i]);
	while (j < ALL_DIRECTION)
	{
		if (j != i && data->cubfile->textures[j])
		{
			len = get_max_value(len, ft_strlen(data->cubfile->textures[j]));
			if (ft_strncmp(data->cubfile->textures[i],
					data->cubfile->textures[j], len) == 0)
				return (false);
		}
		j++;
	}
	return (true);
}

int	xpm_to_img(t_data *data)
{
	int		i;
	void	*tmp;
	t_image	*imgs[ALL_DIRECTION];

	i = 0;
	imgs[0] = &data->tex_n;
	imgs[1] = &data->tex_s;
	imgs[2] = &data->tex_w;
	imgs[3] = &data->tex_e;
	while (i < ALL_DIRECTION)
	{
		tmp = data->cubfile->textures[i];
		read_image(data, imgs[i], tmp);
		free_buf((void **)&tmp);
		if (!imgs[i]->img)
			break ;
		i++;
	}
	return (i);
}
