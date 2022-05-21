/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 16:49:54 by kfumiya           #+#    #+#             */
/*   Updated: 2021/06/05 23:33:36 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int
	str_to_color(t_str *str)
{
	int	i;
	int	color;
	int	tmp;

	i = 0;
	color = 0;
	while (str)
	{
		tmp = ft_atoi(str->content);
		if (tmp < 0 || tmp > 255)
			return (-1);
		color = color | (tmp << (16 - (i++ * 8)));
		str = str->next;
	}
	return (color);
}

int
	parse_color(t_config *config, int key, char const *line)
{
	int				i;
	unsigned int	color;
	t_str			*str[2];

	if (key == C_F && config->set[C_F])
		return (out_error("Error:\nFloor Color already set.\n"));
	else if (key == C_C && config->set[C_C])
		return (out_error("Error:\nCiling Color already set.\n"));
	i = 1;
	while (line[i])
		if (!ft_in_set(line[i++], " ,0123456789"))
			return (0);
	str[0] = NULL;
	str[1] = NULL;
	if (!(str[0] = ft_split(line, ' ')) || str_length(str[0]) != 2
		|| !(str[1] = ft_split(str[0]->next->content, ','))
		|| str_length(str[1]) != 3)
		return (str_clear(&str[0]) || str_clear(&str[1]));
	if ((int)((color = str_to_color(str[1]))) < 0)
		return (str_clear(&str[0]) || str_clear(&str[1]));
	config->c[(key == C_F) ? TEX_FLOOR : TEX_CEILING] = color;
	config->set[key] = 1;
	return ((str_clear(&str[0]) || str_clear(&str[1])) | 1);
}

static int
	get_dimensions(t_config *config, t_str *str)
{
	int		tmp;
	t_str	*param;
	
	param = str->next;
	tmp = ft_atoi(param->content);
	if (tmp <= 1)
		return (str_clear(&str));
	config->requested_width = tmp;
	param = param->next;
	tmp = ft_atoi(param->content);
	if (tmp <= 1)
		return (str_clear(&str));
	config->requested_height = tmp;
	return (1);
}

int
	parse_dimensions(t_config *config, int key, char const *line)
{
	int		i;
	t_str	*str;

	if (config->set[key])
		return (out_error("Error:\nMultiple dimentions inputs\n"));
	config->set[key] = 1;
	i = 0;
	while (line[++i])
		if (line[i] != ' ' && line[i] < '0' && line[i] > '9')
			return (0);
	str = NULL;
	if (!(str = ft_split(line, ' ')) || str_length(str) != 3)
		return (str_clear(&str));
	if (!get_dimensions(config, str))
		return (0);
	return (str_clear(&str) | 1);
}
