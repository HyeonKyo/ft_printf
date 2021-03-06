/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_print.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 18:46:00 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/06/02 18:46:01 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			get_size_based(unsigned long long n, int base)
{
	int	size;

	size = 0;
	if (n == 0)
		size = 1;
	while (n)
	{
		size++;
		n = n / base;
	}
	return (size);
}

char		*pf_itoa_hex(unsigned long long n, t_opt opts)
{
	int		len;
	char	*buf;
	char	*hex;

	len = get_size_based(n, 16);
	buf = (char *)malloc((len + 1) * sizeof(char));
	if (buf == 0)
		return (0);
	buf[len] = 0;
	if (opts.type == 'x' || opts.type == 'p')
		hex = "0123456789abcdef";
	else
		hex = "0123456789ABCDEF";
	if (n == 0)
		buf[0] = '0';
	while (n)
	{
		buf[--len] = hex[n % 16];
		n = n / 16;
	}
	return (buf);
}

char		*pf_itoa_hexcase(unsigned long long n, t_opt opts)
{
	unsigned char	x1;
	unsigned short	x2;
	char			*buf;

	if (opts.ln.hh)
	{
		x1 = (unsigned char)n;
		buf = pf_itoa_hex(x1, opts);
	}
	else if (opts.ln.h)
	{
		x2 = (unsigned short)n;
		buf = pf_itoa_hex(x2, opts);
	}
	else
		buf = pf_itoa_hex(n, opts);
	return (buf);
}

char		*x_pre_task(va_list ap, t_opt *opts, unsigned long long *n)
{
	char	*buf;

	*n = get_arg_u(ap, opts);
	if (opts->fg.space || opts->fg.plus)
		return (0);
	if ((opts->fg.minus && opts->fg.zero) || opts->prec != 0)
		opts->fg.zero = 0;
	buf = pf_itoa_hexcase(*n, *opts);
	if (!buf)
		return (0);
	return (buf);
}
