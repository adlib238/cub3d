/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 11:11:34 by kfumiya           #+#    #+#             */
/*   Updated: 2022/05/22 11:21:03 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <limits.h>

# define BUFFER_SIZE 1024

// size_t	ft_strlen(const char *s);
// char	*ft_substr(char const *s, size_t start, size_t len);
// char	*ft_join(char const *s1, char const *s2);
// char	*ft_strchr(const char *s, int c);
char	*get_next_line(int fd);
char	*no_newline(char **save);
#endif
