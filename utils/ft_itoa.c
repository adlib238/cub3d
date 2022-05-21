/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 19:23:38 by kfumiya           #+#    #+#             */
/*   Updated: 2021/04/13 19:23:40 by kfumiya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int
	ft_abs(int nbr)
{
	return ((nbr < 0) ? -nbr : nbr);
}

static void
	ft_strrev(char *str)
{
	size_t	length;
	size_t	i;
	char	tmp;

	length = ft_strlen(str);
	i = 0;
	while (i < length / 2)
	{
		tmp = str[i];
		str[i] = str[length - i - 1];
		str[length - i - 1] = tmp;
		i++;
	}
}

char
	*ft_itoa(int n)
{
	char	*str;
	int		is_neg;
	int		i;
	size_t	length;

	is_neg = (n < 0);
	if (!(str = (char*)malloc((11 + is_neg) * sizeof(*str))))
		return (NULL);
	i = 0;
	while (i < (12 + is_neg))
		str[i++] = 0;
	if (n == 0)
		str[0] = '0';
	length = 0;
	while (n != 0)
	{
		str[length++] = '0' + ft_abs(n % 10);
		n = (n / 10);
	}
	if (is_neg)
		str[length] = '-';
	ft_strrev(str);
	return (str);
}
