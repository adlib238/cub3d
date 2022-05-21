/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 22:15:27 by kfumiya           #+#    #+#             */
/*   Updated: 2021/06/06 05:38:19 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include <stdlib.h>

# define PTR_CAST(a)	(void*)((uintptr_t)(a))

typedef struct	s_pos
{
	double	x;
	double	y;
}				t_pos;

typedef struct s_pos_fl
{
	float x;
	float y;
} t_pos_fl;


typedef struct	s_str
{
	char			*content;
	struct s_str	*next;
}				t_str;

void set_pos(t_pos *pos, double x, double y);

void copy_pos(t_pos *pos, t_pos *org);

int ft_endwith(char const *str, char const *end);

int str_length(t_str *str);

t_str *str_add_back(t_str **str, char *content);

t_str *str_last(t_str *str);

int str_clear(t_str **list);

int ft_atoi(char const *str);

char *ft_itoa(int n);

void *ft_memmove(void *dst, const void *src, unsigned long len);

t_str *ft_split(char const *org, char sep);

int ft_strcmp(const char *s1, const char *s2);

char *ft_strdup(char const *s1);

int ft_strlen(char const *str);

char *ft_substr(char const *s, int start, int len);

int ft_write_int(char *buf, int val, int start);

int ft_in_set(char c, char const *set);

void set_pos_fl(t_pos_fl *pos, float x, float y);

void copy_pos_fl(t_pos_fl *pos, t_pos_fl *org);

#endif
