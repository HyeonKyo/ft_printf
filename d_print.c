/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_print.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 15:43:05 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/06/02 15:43:07 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*d_pre_task(va_list ap, t_opt *opts, int *n, int *size)
{
	//length고려 코드 추가해야함.
	char	*buf;

	*n = va_arg(ap, int);
	if (opts->fg.hash || (opts->prec == -3 && n == 0))//경메 출력 조건
		return (0);
	if ((opts->fg.minus && opts->fg.zero) || opts->prec == -2)//0 flag 무시조건.
		opts->fg.zero = 0;
	if (opts->prec > 0)
		*size = opts->prec;
	else if (opts->width > 0)
		*size = opts->width;
	buf = pf_itoa(*n, *opts);//pf_itoa는 기호 제외하고 숫자만 출력
	if (!buf)
		return (0);
	return (buf);
}
//공백, 부호, 숫자 or 부호 숫자 공백

size_t	print_sign_buf(int n, char *buf, t_opt opts)
{
	size_t	cnt;

	cnt = 0;
	cnt += print_sign(opts, n);
	write(1, buf, ft_strlen(buf));
	cnt += ft_strlen(buf);
	return (cnt);
}

size_t	d_print_case1(int n, int size, t_opt opts, char *buf)
{
	size_t	cnt;
	int	len;

	cnt = 0;
	len = size - ft_strlen(buf);
	if (opts.fg.plus || n < 0)
		len--;
	if (len > 0 && opts.prec <= 0)
	{
		if (opts.fg.minus)
		{
			cnt += print_sign_buf(n, buf, opts);
			cnt += print_char(' ', len);
		}
		else
		{
			if (!opts.fg.zero)
			{
				cnt += print_char(' ', len);
				cnt += print_sign_buf(n, buf, opts);
			}
		}
	}
	return (cnt);
}

size_t	d_print_case2(int n, int size, t_opt opts, char *buf)//정상 출력, 부호+0+숫자 출력
{
	size_t	cnt;
	int	len;

	cnt = 0;
	len = size - ft_strlen(buf);
	cnt += print_sign(opts, n);
	if (len > 0)
	{
		if (opts.prec > 0)
			cnt += print_char('0', len);
		else
		{
			if (!opts.fg.minus && opts.fg.zero)
			{
				len--;
				cnt += print_char('0', len);
			}
		}
	}
	write(1, buf, ft_strlen(buf));
	cnt += ft_strlen(buf);
	return (cnt);
}

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
	if (!(*cnt = d_print_case1(n, size, opts, buf)))
		*cnt = d_print_case2(n, size, opts, buf);
}
