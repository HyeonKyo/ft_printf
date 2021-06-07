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

char	*u_pre_task(va_list ap, t_opt *opts, unsigned int *n)
{
	char	*buf;

	*n = va_arg(ap, unsigned int);
	if (opts->fg.hash || opts->fg.space || opts->fg.plus)//경메 출력 조건
		return (0);
	if ((opts->fg.minus && opts->fg.zero) || opts->prec != 0)//0 flag 무시조건.
		opts->fg.zero = 0;
	buf = pf_itoa((long long)*n);//pf_itoa는 기호 제외하고 숫자만 출력
	if (!buf)
		return (0);
	return (buf);
}
//공백, 부호, 숫자 or 부호 숫자 공백

size_t	u_print_case(t_opt opts, char *buf)
{
	size_t	cnt;
	int		buf_len;
	int		zero_len;
	int		print_len;
	int		len;

	cnt = 0;
	buf_len = (int)ft_strlen(buf);
	zero_len = opts.prec - buf_len;
	print_len = buf_len;
	if (zero_len > 0)
		print_len += zero_len;
	len = opts.width - print_len;
	if (buf == 0)
	{
		print_char(' ', len);
		return (len);
	}
	if (len > 0 && !opts.fg.minus)
	{
		if (opts.fg.zero && opts.prec == 0)
			cnt += print_char('0', len);
		else
			cnt += print_char(' ', len);
		if (zero_len > 0)
			cnt += print_char('0', zero_len);
		cnt += print_str(buf, buf_len);
	}
	else
	{
		if (zero_len > 0)
			cnt += print_char('0', zero_len);
		cnt += print_str(buf, buf_len);
		if (len > 0)
			cnt += print_char(' ', len);
	}
	return (cnt);
}

void	u_print(va_list ap, t_opt opts, size_t *cnt)
{
	unsigned int    n;
	char	        *buf;

	n = 0;
	buf = u_pre_task(ap, &opts, &n);
	if (buf == 0)
		return ;
	if (opts.prec < 0  && n == 0)
	{
		free(buf);
		buf = 0;
	}
	*cnt += u_print_case(opts, buf);
	if (buf)
		free(buf);
}
//1.마이너스 플래그 prec(0) + 숫자 + 공백
//2.공백 + prec(0) + 숫자
//3. zero플래그0 + 숫자