/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_print2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 15:48:15 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/06/20 15:48:16 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	print_hex(t_opt opts, int *flag)
{
	if (opts.fg.hash)
	{
		*flag = 0;
		if (opts.type == 'x')
			return (print_str("0x", 2));
		return (print_str("0X", 2));
	}
	return (0);
}

static size_t	zero_print(int len, t_opt opts, int *flag)
{
	size_t	cnt;

	cnt = 0;
	if (*flag)
		cnt = print_hex(opts, flag);
	cnt += print_char('0', len);
	return (cnt);
}

static size_t	x_print_case(int zero_len, int len, char *buf, t_opt opts)
{
	size_t	cnt;
	int		flag;

	cnt = 0;
	if (buf[0] == '0' && opts.prec < 0)
		return (print_char(' ', len));
	flag = 1;
	if (buf[0] == '0')
		flag = 0;
	if (!opts.fg.minus)
	{
		if (opts.fg.zero)
			cnt += zero_print(len, opts, &flag);
		else
			cnt += print_char(' ', len);
		cnt += zero_print(zero_len, opts, &flag);
		cnt += print_str(buf, ft_strlen(buf));
	}
	else
	{
		cnt += zero_print(zero_len, opts, &flag);
		cnt += print_str(buf, ft_strlen(buf));
		cnt += print_char(' ', len);
	}
	return (cnt);
}

static size_t	x_print_all(t_opt opts, char *buf)
{
	int		buf_len;
	int		zero_len;
	int		len;

	buf_len = (int)ft_strlen(buf);
	zero_len = opts.prec - buf_len;
	len = opts.width - buf_len;
	if (zero_len > 0)
		len -= zero_len;
	if (opts.fg.hash && buf[0] != '0')
		len -= 2;
	if (opts.prec < 0 && buf[0] == '0')
		len++;
	return (x_print_case(zero_len, len, buf, opts));
}
/*
** buf_len : 숫자 길이
** zero_len : prec에 의한 0출력 길이
** len : 숫자+0출력 후 남은 공백, 0출력 길이
*/

void			x_print(va_list ap, t_opt opts, size_t *cnt)
{
	unsigned long long	n;
	char				*buf;

	n = 0;
	buf = x_pre_task(ap, &opts, &n);
	if (buf == 0)
		return ;
	*cnt += x_print_all(opts, buf);
	if (buf)
		free(buf);
}
