/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_print.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 19:07:26 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/06/09 19:07:29 by hyeonkki         ###   ########.fr       */
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

size_t	c_case_print(int c, t_opt opts)
{
	if (opts.ln.l)
	{
		if (c >= 65536)
			return (c4_print(c));
		if (c >= 2048)
			return (c3_print(c));
		if (c >= 128)
			return (c2_print(c));
		return (c1_print(c));
	}
	return (c1_print(c));
}

int		c_case_cnt(int c, t_opt opts)
{
	if (!opts.ln.l)
		return (1);
	if (c >= 65536)
		return (4);
	if (c >= 2048)
		return (3);
	if (c >= 128)
		return (2);
	return (1);
}

void	c_print(va_list ap, t_opt opts, size_t *cnt)
{
	int	c;

	if (opts.type == '%')
		c = '%';
	else
		c = va_arg(ap, int);
	//2. width가 0이면 그냥 문자 출력하면 됨.
	if (opts.width == 0)
		*cnt += c_case_print(c, opts);
	//3. width가 있으면 minus옵션이 있는 경우와 없는 경우로 나뉨.
	else if (opts.fg.minus == 1)
	{
		*cnt += c_case_print(c, opts);
		*cnt += print_char(' ', opts.width - c_case_cnt(c, opts));
	}
	else
	{
		if (opts.type == '%' && opts.fg.zero)
			*cnt += print_char('0', opts.width - c_case_cnt(c, opts));
		else
			*cnt += print_char(' ', opts.width - c_case_cnt(c, opts));
		*cnt += c_case_print(c, opts);
	}
}

/*
1. int로 받아줌
2. 그 받은 인자의 범위 탐색
3. 맞는 범위의 출력으로 감.
	=> 비트연산으로 출력.
*/