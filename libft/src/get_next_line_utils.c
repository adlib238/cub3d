/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 11:11:09 by kfumiya           #+#    #+#             */
/*   Updated: 2022/05/23 13:44:27 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*no_newline(char **save)
{
	char	*line;

	if (**save == '\0')
		return (NULL);
	line = ft_strsub(*save, 0, ft_strlen(*save));
	if (line == NULL)
		return (NULL);
	return (line);
}
