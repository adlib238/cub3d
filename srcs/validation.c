/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 22:48:14 by mmasubuc          #+#    #+#             */
/*   Updated: 2022/06/16 23:53:49 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	is_valid_argv(int argc, char **argv)
{
	int		i;
	size_t	len;
	char	*str;

	i = 0;
	str = NULL;
	if (argc != 2)
		exit_program(INVALID_ARG, NULL, 0);
	len = get_max_value(ft_strlen(argv[1]), 4);
	if (ft_strncmp(argv[1], ".cub", len) == 0)
		exit_program(INVALID_ARG, NULL, 0);
	while (argv[1][i] != '\0')
	{
		if (argv[1][i] == '.')
		{
			if (!is_extension(argv[1], i))
				exit_program(INVALID_ARG, NULL, 0);
			str = &argv[1][i];
		}
		i++;
	}
	if (!str || ft_strlen(str) != 4
		|| ft_strncmp(str, ".cub", 4) != 0)
		exit_program(INVALID_ARG, NULL, 0);
}

bool	is_extension(char *arg, int i)
{
	size_t	len;

	len = get_max_value(ft_strlen(&arg[i]), 4);
	if (i > 1 && arg[i - 1] == '/' && ft_strncmp(&arg[i], ".cub", len) == 0)
		return (false);
	return (true);
}
