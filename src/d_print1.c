/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_print1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 15:39:10 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/06/20 15:40:00 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static long long	get_arg_d(va_list ap, t_opt *opts)
{
	if (opts->ln.l)
		return ((long long)va_arg(ap, long));
	if (opts->ln.ll)
		return ((long long)va_arg(ap, long long));
	return ((long long)va_arg(ap, int));
}

static char			*pf_itoa_case(long long *n, t_opt *opts)
{
	char	d1;
	short	d2;
	char	*buf;

	if (opts->ln.hh)
	{
		d1 = (char)*n;
		buf = pf_itoa(d1);
		*n = (long long)d1;
	}
	else if (opts->ln.h)
	{
		d2 = (short)*n;
		buf = pf_itoa(d2);
		*n = (long long)d2;
	}
	else
		buf = pf_itoa(*n);
	return (buf);
}

char				*d_pre_task(va_list ap, t_opt *opts, long long *n)
{
	char	*buf;

	*n = get_arg_d(ap, opts);
	if (opts->fg.hash)
		return (0);
	if ((opts->fg.minus && opts->fg.zero) || opts->prec != 0)
		opts->fg.zero = 0;
	buf = pf_itoa_case(n, opts);
	if (!buf)
		return (0);
	return (buf);
}
/*
** pf_itoa는 기호 제외하고 숫자만 출력
*/
