/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:04:49 by mmasubuc          #+#    #+#             */
/*   Updated: 2022/06/16 20:09:31 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>
# include <fcntl.h>
# include "get_next_line.h"

// parse_cubfiles.c
void		parse_cubfile(t_data *data, char *file);
char		**set_types(void);
void		get_info(t_data *data, int fd, char **types);
bool		check_type(t_data *data, char *line, char **types);
bool		count_row_col(t_data *data, int fd);

// parse_textures.c
bool		parse_textures(t_data *data, char *line, int i);
bool		is_unique_texture(t_data *data, int i);
int			xpm_to_img(t_data *data);

// parse_colors.c
bool		parse_color(t_data *data, char *line, int i);
bool		get_color(t_data *data, int index, char *line);
bool		is_valid_num(char **s_nums, int *nums);
uint32_t	rgb_to_hex(int red, int green, int blue);
bool		is_unique_color(t_data *data, int index);

// parse_map.c
void		parse_map(t_data *data, char *file);
void		read_through_type_info(int fd, t_data *data);
bool		read_map(t_data *data, int fd);
bool		get_ppos(t_data *data, char *line, int row);
bool		is_closed_by_wall(char **map, int row, int col, t_data *data);

#endif
