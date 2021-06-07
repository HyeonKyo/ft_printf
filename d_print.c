/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_print.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 15:43:05 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/06/05 15:20:54 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*d_pre_task(va_list ap, t_opt *opts, int *n, int *size)
{
	char	*buf;

	*n = va_arg(ap, int);
	if (opts->fg.hash || (opts->prec < 0  && *n == 0 && !opts->width))//경메 출력 조건
		return (0);
	if ((opts->fg.minus && opts->fg.zero) || opts->prec != 0)//0 flag 무시조건.
		opts->fg.zero = 0;
	if (opts->prec == -2)
		opts->fg.minus = 0;
	if (opts->prec >= opts->width)
	{
		*size = opts->prec;
		if (opts->fg.plus || opts->fg.space || n < 0)
			(*size)++;
	}
	else if (opts->width > opts->prec)
		*size = opts->width;
	buf = pf_itoa(*n);//pf_itoa는 기호 제외하고 숫자만 출력
	if (!buf)
		return (0);
	return (buf);
}
//공백, 부호, 숫자 or 부호 숫자 공백
size_t	print_prec_buf(int n, t_opt opts, char *buf)
{
	int		buf_len;
	size_t	cnt;

	cnt = 0;
	buf_len = (int)ft_strlen(buf);
	if (!opts.fg.zero)
		cnt += print_sign(opts, n);
	if (opts.prec > buf_len)
		cnt += print_char('0', opts.prec - buf_len);
	cnt += print_str(buf, buf_len);
	return (cnt);
}

size_t	d_print_case(int n, int size, t_opt opts, char *buf)//prec있는 경우 && prec > buf_len인 경우
{
	size_t	cnt;
	int		buf_len;
	size_t	print_len;

	cnt = 0;
	buf_len = (int)ft_strlen(buf);
	if (opts.prec < 0  && n == 0)
		buf_len = 0;
	if (buf_len == 0)
	{
		cnt += print_char(' ', opts.width);
		return (cnt);
	}
	if (size > buf_len)
	{
		if (opts.fg.minus)
			cnt += print_prec_buf(n, opts, buf);
		if (opts.width > opts.prec)
		{
			if (opts.prec > buf_len)
				print_len = opts.width - opts.prec;
			else
				print_len = opts.width - buf_len;
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
//1. prec or width가 buf의 길이보다 작은 경우는 buf정상 출력(flag만 고려)
	//2. width만 있는 경우 buf_len, sign만큼 뺀 나머지 0 or 공백 출력(flag : zero minus plus)
	//3. prec만 있는 경우 sign제외한 n - buf_len만큼 0을 채워주면서 출력
	//3. prec > buf_len인 경우
	//		=> 1. prec > width인 경우 -> width무시하고 prec만큼 0붙여서 출력(flag 정상출력 됨.)
	//		=> 2. prec < width인 경우 -> width - (sign + prec)만큼 공백, 문자는 기호 + 0 + 숫자

void	d_print(va_list ap, t_opt opts, size_t *cnt)
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
