/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_print.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 15:43:05 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/06/08 15:10:22 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*d_pre_task(va_list ap, t_opt *opts, int *n, int *size)
{
	char	*buf;

	*n = va_arg(ap, int);
	if (opts->fg.hash || (opts->prec < 0  && *n == 0 && !opts->width))//경메 출력 조건
		return (0);
	if ((opts->fg.minus && opts->fg.zero) || opts->prec != 0)//0 flag 무시조건.
		opts->fg.zero = 0;
	if (opts->prec >= opts->width)
	{
		*size = opts->prec;
		if (opts->fg.plus || opts->fg.space || *n < 0)
			(*size)++;
	}
	else if (opts->width > opts->prec)
		*size = opts->width;
	buf = pf_itoa(*n);//pf_itoa는 기호 제외하고 숫자만 출력
	if (!buf)
		return (0);
	return (buf);
}

static size_t	print_prec_buf(int n, t_opt opts, char *buf)
{
	int		buf_len;
	size_t	cnt;

	cnt = 0;
	buf_len = (int)ft_strlen(buf);
	if (!opts.fg.zero)//이거 왜 있지?
		cnt += print_sign(opts, n);
	if (opts.prec > buf_len)
		cnt += print_char('0', opts.prec - buf_len);
	cnt += print_str(buf, buf_len);
	return (cnt);
}

static size_t	zero_or_space(int n, int buf_len, t_opt opts)
{
	size_t	print_len;
	size_t	cnt;

	print_len = 0;
	cnt = 0;
	if (opts.width > opts.prec)
	{
		print_len = opts.width - buf_len;//공백 or 0출력 길이
		if (opts.prec > buf_len)
			print_len = opts.width - opts.prec;
		if (opts.fg.plus || opts.fg.space || n < 0)//부호 출력 시
			print_len--;
		if (!opts.fg.zero)
			cnt += print_char(' ', print_len);
		else
		{
			cnt += print_sign(opts, n);
			cnt += print_char('0', print_len);
		}
	}
	return (cnt);
}

static size_t	d_print_case(int n, int size, t_opt opts, char *buf)
{
	size_t	cnt;
	int		buf_len;

	cnt = 0;
	buf_len = (int)ft_strlen(buf);
	if (opts.prec < 0  && n == 0)
		cnt += print_char(' ', opts.width);
	else if (size > buf_len)
	{
		if (opts.fg.minus)
			cnt += print_prec_buf(n, opts, buf);
		cnt += zero_or_space(n, buf_len, opts);
		if (!opts.fg.minus)
			cnt += print_prec_buf(n, opts, buf);
	}
	else
	{
		cnt += print_sign(opts, n);
		cnt += print_str(buf, ft_strlen(buf));
	}
	return (cnt);
}

void			d_print(va_list ap, t_opt opts, size_t *cnt)
{
	int		n;
	int		size;
	char	*buf;

	n = 0;
	size = 0;
	buf = d_pre_task(ap, &opts, &n, &size);
	if (buf == 0)
		return ;
	*cnt += d_print_case(n, size, opts, buf);
	if (buf)
		free(buf);
}
