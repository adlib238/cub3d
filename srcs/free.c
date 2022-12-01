/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 18:36:26 by mmasubuc          #+#    #+#             */
/*   Updated: 2022/06/15 13:48:50 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_2d_array(char **content)
{
	int	i;

	i = 0;
	while (content[i] != NULL)
	{
		free(content[i]);
		content[i] = NULL;
		i++;
	}
	free(content);
	content = NULL;
}

void	free_buf(void **buf)
{
	free(*buf);
	*buf = NULL;
}

void	free_mlx(t_data *data, t_type type)
{
	if (type >= 1)
		mlx_destroy_image(data->mlx, data->tex_n.img);
	if (type >= 2)
		mlx_destroy_image(data->mlx, data->tex_s.img);
	if (type >= 3)
		mlx_destroy_image(data->mlx, data->tex_w.img);
	if (type == 4)
		mlx_destroy_image(data->mlx, data->tex_e.img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
		mlx_destroy_display(data->mlx);
}

void	free_data(t_data *data)
{
	free_2d_array(data->cubfile->map);
	free(data->cubfile);
}
