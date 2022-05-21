/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 18:52:42 by kfumiya           #+#    #+#             */
/*   Updated: 2021/06/05 23:22:39 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char
	*read_path(int start, char const *line)
{
	int		start_def;
	int		end;
	char	*path;

	start_def = start;
	if (!line)
		return (NULL);
	while (line[start] && line[start] == ' ')
		start++;
	end = ft_strlen(line);
	while (line[end] == ' ')
		end--;
	if (start == start_def || end - start <= 0
		|| !(path = ft_substr(line, start, end - start)))
		return (NULL);
	return (path);
}

static int
	texture_index(int key)
{
	if (key == C_NO)
		return (TEX_NORTH);
	else if (key == C_SO)
		return (TEX_SOUTH);
	else if (key == C_WE)
		return (TEX_WEST);
	else if (key == C_EA)
		return (TEX_EAST);
	return (TEX_SPRITE);
}

static int
	check_txt(int *set, int key)
{
	if (key == C_NO && set[C_NO])
		return (out_error("Error:\nNORTH Texture already set.\n"));
	if (key == C_SO && set[C_SO])
		return (out_error("Error:\nSOUTH Texture already set.\n"));
	if (key == C_WE && set[C_WE])
		return (out_error("Error:\nWEST Texture already set.\n"));
	if (key == C_EA && set[C_EA])
		return (out_error("Error:\nEAST Texture already set.\n"));
	if (key == C_S && set[C_S])
		return (out_error("Error:\nSPRITE Texture already set.\n"));
	return (1);
}

int
	parse_textures(t_config *config, int key, char const *line)
{
	char	*path;
	int		index;

	if (!(check_txt(config->set, key)))
		return (0);
	index = texture_index(key);
	if (config->tex_path[index])
	{
		free(config->tex_path[index]);
		config->tex_path[index] = NULL;
	}
	if (!(path = read_path((index == TEX_SPRITE) ? 1 : 2, line)))
		return (0);
	config->tex_path[index] = path;
	config->set[key] = 1;
	return (1);
}
