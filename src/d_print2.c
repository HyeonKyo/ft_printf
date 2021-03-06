/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_print2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 14:36:02 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/06/20 14:36:03 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	zero_or_space(long long n, int space_len, t_opt opts, int *flag)
{
	size_t	cnt;

	if (space_len <= 0)
		return (0);
	cnt = 0;
	if (check_sign(opts, n))
		*flag = 1;
	if (opts.fg.zero)
	{
		cnt = print_sign(opts, n);
		cnt += print_char('0', space_len);
	}
	else
	{
		cnt += print_char(' ', space_len);
		if (!opts.fg.minus && !(opts.prec < 0 && n == 0))
			cnt += print_sign(opts, n);
	}
	return (cnt);
}

static size_t	print_digit(long long n, t_opt opts, char *buf, int flag)
{
	size_t	cnt;
	int		buf_len;
	int		prec_len;

	cnt = 0;
	if (n == 0 && opts.prec < 0)
		return (print_sign(opts, n));
	buf_len = ft_strlen(buf);
	prec_len = opts.prec - buf_len;
	if (flag == 0)
		cnt = print_sign(opts, n);
	if (prec_len > 0)
		cnt += print_char('0', prec_len);
	cnt += print_str(buf, buf_len);
	return (cnt);
}

static size_t	d_print_all(long long n, t_opt opts, char *buf)
{
	size_t	cnt;
	int		buf_len;
	int		print_len;
	int		space_len;
	int		flag;

	cnt = 0;
	flag = 0;
	buf_len = (int)ft_strlen(buf);
	print_len = buf_len;
	if (opts.prec > buf_len)
		print_len = opts.prec;
	else if (opts.prec < 0 && n == 0)
		print_len = 0;
	space_len = opts.width - print_len - check_sign(opts, n);
	if (!opts.fg.minus)
		cnt += zero_or_space(n, space_len, opts, &flag);
	cnt += print_digit(n, opts, buf, flag);
	if (opts.fg.minus)
		cnt += zero_or_space(n, space_len, opts, &flag);
	return (cnt);
}

void			d_print(va_list ap, t_opt opts, size_t *cnt)
{
	long long	n;
	char		*buf;

	n = 0;
	buf = d_pre_task(ap, &opts, &n);
	if (buf == 0)
		return ;
	*cnt += d_print_all(n, opts, buf);
	if (buf)
		free(buf);
}
