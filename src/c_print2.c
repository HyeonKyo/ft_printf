/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_print2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 14:28:33 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/06/20 14:28:34 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
	if (opts.width == 0)
		*cnt += c_case_print(c, opts);
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
** width가 0이면 그냥 문자 출력하면 됨.
** width가 있으면 minus옵션이 있는 경우와 없는 경우로 나뉨.
*/
