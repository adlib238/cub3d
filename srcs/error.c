/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 10:04:36 by kfumiya           #+#    #+#             */
/*   Updated: 2022/06/13 13:26:43 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	put_err_msg(char *msg)
{
	write(STDERR_FILENO, "Error: ", ft_strlen("Error: "));
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
}

int
	return_error_msg(char *msg)
{
	put_err_msg(msg);
	return (ERROR);
}
