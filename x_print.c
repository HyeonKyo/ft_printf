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

int		get_size_based(unsigned long long n, int base)
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

char			*pf_itoa_hexcase(unsigned long long n, t_opt opts)
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

static char	*x_pre_task(va_list ap, t_opt *opts, unsigned long long *n)
{
	char	*buf;

	*n = get_arg_u(ap, opts);
	if (opts->fg.space || opts->fg.plus)//경메 출력 조건
		return (0);
	if ((opts->fg.minus && opts->fg.zero) || opts->prec != 0)//0 flag 무시조건.
		opts->fg.zero = 0;
	buf = pf_itoa_hexcase(*n, *opts);
	if (!buf)
		return (0);
	return (buf);
}

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

size_t	x_print_case(int zero_len, int len, char *buf, t_opt opts)
{
	size_t	cnt;
	int		buf_len;
	int		flag;

	cnt = 0;
	if (buf[0] == '0' && opts.prec < 0)
		return (print_char(' ', len));
	flag = 1;
	if (buf[0] == '0')
		flag = 0;
	buf_len = (int)ft_strlen(buf);
	if (!opts.fg.minus)
	{
		if (opts.fg.zero)
			cnt += zero_print(len, opts, &flag);
		else
			cnt += print_char(' ', len);
		cnt += zero_print(zero_len, opts, &flag);
		cnt += print_str(buf, buf_len);
	}
	else
	{
		cnt += zero_print(zero_len, opts, &flag);
		cnt += print_str(buf, buf_len);
		cnt += print_char(' ', len);
	}
	return (cnt);
}

size_t			x_print_all(t_opt opts, char *buf)
{
	int		buf_len;
	int		zero_len;
	int		len;

	buf_len = (int)ft_strlen(buf);//숫자 길이
	zero_len = opts.prec - buf_len;//prec에 의한 0출력 길이
	len = opts.width - buf_len;//숫자or0출력 후 남은 공백, 0출력 길이
	if (zero_len > 0)
		len -= zero_len;
	if (opts.fg.hash && buf[0] != '0')
		len -= 2;
	if (opts.prec < 0 && buf[0] == '0')
		len++;
	return (x_print_case(zero_len, len, buf, opts));
}

void		x_print(va_list ap, t_opt opts, size_t *cnt)
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
