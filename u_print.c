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

unsigned long long	get_arg_u(va_list ap, t_opt *opts)
{
	if (opts->ln.l)
		return ((unsigned long long)va_arg(ap, unsigned long));
	if (opts->ln.ll)
		return ((unsigned long long)va_arg(ap, unsigned long long));
	return ((unsigned long long)va_arg(ap, unsigned int));
}

char			*pf_uitoa_case(unsigned long long n, t_opt *opts)
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

static char		*u_pre_task(va_list ap, t_opt *opts, unsigned long long *n)
{
	char	*buf;

	*n = get_arg_u(ap, opts);
	if (opts->fg.hash || opts->fg.space || opts->fg.plus)//경메 출력 조건
		return (0);
	if ((opts->fg.minus && opts->fg.zero) || opts->prec != 0)//0 flag 무시조건.
		opts->fg.zero = 0;
	buf = pf_uitoa_case(*n, opts);
	if (!buf)
		return (0);
	return (buf);
}

static size_t	u_print_case(int zero_len, int len, char *buf, t_opt opts)
{
	size_t	cnt;
	int		buf_len;

	cnt = 0;
	buf_len = (int)ft_strlen(buf);
	if (buf == 0)//.0(.) + 0인 경우
		cnt += print_char(' ', len);
	else if (!opts.fg.minus)
	{
		if (opts.fg.zero)
			cnt += print_char('0', len);
		else
			cnt += print_char(' ', len);
		cnt += print_char('0', zero_len);
		cnt += print_str(buf, buf_len);
	}
	else
	{
		cnt += print_char('0', zero_len);
		cnt += print_str(buf, buf_len);
		cnt += print_char(' ', len);
	}
	return (cnt);
}

size_t			u_print_all(t_opt opts, char *buf)
{
	int		buf_len;
	int		zero_len;
	int		len;

	buf_len = (int)ft_strlen(buf);//숫자 길이
	zero_len = opts.prec - buf_len;//prec에 의한 0출력 길이
	len = opts.width - buf_len;//숫자or0출력 후 남은 공백, 0출력 길이
	if (zero_len > 0)
		len -= zero_len;
	return (u_print_case(zero_len, len, buf, opts));
}

void	u_print(va_list ap, t_opt opts, size_t *cnt)
{
	unsigned long long	n;
	char				*buf;

	n = 0;
	buf = u_pre_task(ap, &opts, &n);
	if (buf == 0)
		return ;
	if (opts.prec < 0  && n == 0)
	{
		free(buf);
		buf = 0;
	}
	*cnt += u_print_all(opts, buf);
	if (buf)
		free(buf);
}
