/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:30:44 by mmasubuc          #+#    #+#             */
/*   Updated: 2022/06/17 11:13:55 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"

bool	parse_color(t_data *data, char *line, int i)
{
	size_t	start;

	if (data->cubfile->colors[i - 4] != RGB_MAX + 1 || line[1] == '\0')
		return (false);
	else
	{
		start = 1 + skip_spaces(&line[1]);
		if (!get_color(data, i - 4, &line[start]))
			return (false);
		return (true);
	}
}

bool	get_color(t_data *data, int index, char *line)
{
	int		nums[3];
	size_t	i;
	char	**s_nums;

	i = 0;
	if (line[0] == ',' || line[ft_strlen(line) - 1] == ',')
		return (false);
	s_nums = ft_split(line, ',');
	if (!s_nums)
		exit_program(MALLOC_FAIL, data, 0);
	while (s_nums[i] != NULL && i < 4)
		i++;
	if (i == 3 && is_valid_num(s_nums, nums))
	{
		data->cubfile->colors[index] = rgb_to_hex(nums[0], nums[1], nums[2]);
		free_2d_array(s_nums);
		if (!is_unique_color(data, index))
			return (false);
		return (true);
	}
	free_2d_array(s_nums);
	return (false);
}

bool	is_valid_num(char **s_nums, int *nums)
{
	size_t	i;
	size_t	j;
	int		overflow;

	i = 0;
	overflow = 0;
	while (s_nums[i])
	{
		j = skip_spaces(s_nums[i]);
		if (s_nums[i][j] == '\0')
			return (false);
		while (s_nums[i][j] != '\0' && ft_isdigit(s_nums[i][j]) == 1)
			j++;
		if (i != 2)
			j += skip_spaces(&s_nums[i][j]);
		if (s_nums[i][j] != '\0')
			return (false);
		nums[i] = ft_atoi(s_nums[i], &overflow);
		if (overflow == 1 || !(0 <= nums[i] && nums[i] <= 255))
			return (false);
		i++;
	}
	return (true);
}

uint32_t	rgb_to_hex(int red, int green, int blue)
{
	return (((red & 0xff) << 16) + ((green & 0xff) << 8) + (blue & 0xff));
}

bool	is_unique_color(t_data *data, int index)
{
	int	j;

	j = 0;
	if (index == 0)
		j = 1;
	if (data->cubfile->colors[j] != RGB_MAX + 1
		&& data->cubfile->colors[index] == data->cubfile->colors[j])
		return (false);
	return (true);
}
