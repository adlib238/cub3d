/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:07:05 by mmasubuc          #+#    #+#             */
/*   Updated: 2022/06/14 23:00:52 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_program(char *msg, t_data *data, t_type type)
{
	size_t	msg_len;

	msg_len = ft_strlen(msg);
	if (msg_len != ft_strlen(INVALID_ARG)
		|| ft_strncmp(msg, INVALID_ARG, msg_len != 0))
		free_mlx(data, type);
	ft_putstr_fd("Error\n", 2);
	ft_putendl_fd(msg, 2);
	exit(EXIT_FAILURE);
}

int	close_window(t_data *data)
{
	free_mlx(data, ALL_DIRECTION);
	free_data(data);
	exit(EXIT_SUCCESS);
}
