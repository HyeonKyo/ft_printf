/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_print1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 14:48:22 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/06/20 14:48:23 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	c1_print(int c)
{
	write(1, &c, 1);
	return (1);
}

size_t	c2_print(int n)
{
	unsigned char	buf;

	buf = (n >> 6) | 192;
	write(1, &buf, 1);
	buf = (n & 63) | 128;
	write(1, &buf, 1);
	return (2);
}

size_t	c3_print(int n)
{
	unsigned char	buf;

	buf = (n >> 12) | 224;
	write(1, &buf, 1);
	buf = ((n >> 6) & 63) | 128;
	write(1, &buf, 1);
	buf = (n & 63) | 128;
	write(1, &buf, 1);
	return (3);
}

size_t	c4_print(int n)
{
	unsigned char	buf;

	buf = (n >> 18) | 240;
	write(1, &buf, 1);
	buf = ((n >> 12) & 63) | 128;
	write(1, &buf, 1);
	buf = ((n >> 6) & 63) | 128;
	write(1, &buf, 1);
	buf = (n & 63) | 128;
	write(1, &buf, 1);
	return (4);
}
