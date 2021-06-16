/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 16:51:00 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/06/14 16:51:01 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	trans_to_bin(int *bits, size_t num)//10진수를 2진수로
{
	int	i;
	int	j;
	int	buf[64];

	i = 0;
	j = 0;
	while (i < 64)
	{
		buf[i++] = num % 2;
		num /= 2;
	}
	while (i)
		bits[j++] = buf[--i];
}

size_t		power(int base, int e)//거듭제곱 함수
{
	size_t	n;

	n = 1;
	if (e <= 0)
		return (1);
	if (base == 0)
		return (0);
	while (e)
	{
		n *= base;
		e--;	
	}
	return (n);
}

int		trans_to_dex(int *bits, int size)//2진수 -> 10진수
{
	int	n;
	int	i;

	n = 0;
	i = 0;
	while (size)
		n += bits[--size] * (int)power(2, i++);
	return (n);
}
