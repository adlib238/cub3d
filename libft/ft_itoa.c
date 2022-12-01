/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 21:00:12 by mmasubuc          #+#    #+#             */
/*   Updated: 2021/12/11 17:57:45 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_get_digit(int n)
{
	unsigned int	nb;
	unsigned int	digit;

	if (n == 0)
		return (1);
	digit = 0;
	if (n < 0)
	{
		nb = -n;
		digit++;
	}
	else
		nb = n;
	while (nb > 0)
	{
		nb /= 10;
		digit++;
	}
	return (digit);
}

char	*ft_itoa(int n)
{
	char			*array;
	unsigned int	nb;
	unsigned int	digit;

	if (n < 0)
		nb = (-1) * n;
	else
		nb = n;
	digit = ft_get_digit(n);
	array = (char *)malloc(digit + 1);
	if (!array)
		return (NULL);
	array[digit] = '\0';
	if (n < 0)
		array[0] = '-';
	while (nb > 0)
	{
		array[--digit] = nb % 10 + '0';
		nb = nb / 10;
	}
	if (n == 0)
		array[0] = 0 + '0';
	return (array);
}
