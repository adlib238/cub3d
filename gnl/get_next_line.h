/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 00:10:45 by kfumiya           #+#    #+#             */
/*   Updated: 2021/04/13 19:50:50 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

# ifndef FD_MAX
#  define FD_MAX 256
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

int		ft_strlen(const char *str);
void	*ft_memmove(void *s1, const void *s2, size_t len);
char	*gnl_strjoin(char const *s1, char const *s2);
int		find_nl(char *save);
char	*write_line(char *save);
char	*save_line(char *save);
int		free_null(void *ptr);
int		get_next_line(int fd, char **line);

#endif
