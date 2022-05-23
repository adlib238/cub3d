/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 19:34:15 by kfumiya           #+#    #+#             */
/*   Updated: 2022/05/23 11:14:57 by kfumiya          ###   ########.fr       */
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