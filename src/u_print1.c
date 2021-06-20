/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_print.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 18:45:53 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/06/02 18:45:54 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_ull		get_arg_u(va_list ap, t_opt *opts)
{
	if (opts->ln.l)
		return ((unsigned long long)va_arg(ap, unsigned long));
	if (opts->ln.ll)
		return ((unsigned long long)va_arg(ap, unsigned long long));
	return ((unsigned long long)va_arg(ap, unsigned int));
}

static char	*pf_uitoa_case(unsigned long long n, t_opt *opts)
{
	unsigned char	u1;
	unsigned short	u2;
	char			*buf;

	if (opts->ln.hh)
	{
		u1 = (unsigned char)n;
		buf = pf_uitoa(u1);
	}
	else if (opts->ln.h)
	{
		u2 = (unsigned short)n;
		buf = pf_uitoa(u2);
	}
	else
		buf = pf_uitoa(n);
	return (buf);
}

char		*u_pre_task(va_list ap, t_opt *opts, t_ull *n)
{
	char	*buf;

	*n = get_arg_u(ap, opts);
	if (opts->fg.hash || opts->fg.space || opts->fg.plus)
		return (0);
	if ((opts->fg.minus && opts->fg.zero) || opts->prec != 0)
		opts->fg.zero = 0;
	buf = pf_uitoa_case(*n, opts);
	if (!buf)
		return (0);
	return (buf);
}
