/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_print.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 19:07:57 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/06/09 19:07:58 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*p_pre_task(va_list ap, t_opt *opts, int *size)
{
	unsigned long long	n;
	void				*buf;

	n = va_arg(ap, unsigned long long);
	if (opts->fg.hash || opts->fg.plus || opts->fg.space || opts->fg.zero
	|| opts->fg.apos)
		return (0);
	if (opts->width > 0)
		*size = opts->width;
	buf = pf_itoa_hex(n, *opts);
	if (!buf)
		return (0);
	return (buf);
}

static size_t	print_hex_addr(char *buf, t_opt opts)
{
	size_t	n;

	n = 0;
	write(1, "0x", 2);
	if (!(opts.prec == -2 && buf[0] == '0'))
		n = print_str(buf, ft_strlen(buf));
	return (2 + n);
}
/*
** 0x와 문자열 출력 함수
** if문 => 0x만 출력되는 경우가 아니라면.
*/

static size_t	p_print_case(int print_size, t_opt opts, char *buf)
{
	size_t	cnt;
	int		len;

	cnt = 0;
	len = print_size - (ft_strlen(buf) + 2);
	if (opts.prec == -2 && buf[0] == '0')
		len++;
	if (!opts.fg.minus)
		cnt += print_char(' ', len);
	cnt += print_hex_addr(buf, opts);
	if (opts.fg.minus)
		cnt += print_char(' ', len);
	return (cnt);
}
/*
** len : 0x와 문자열 출력
** //0x0이 아닌 0X만 출력되는 경우 => 공백 길이++.
*/

void			p_print(va_list ap, t_opt opts, size_t *cnt)
{
	int					size;
	char				*buf;

	size = 0;
	buf = p_pre_task(ap, &opts, &size);
	if (buf == 0)
		return ;
	*cnt += p_print_case(size, opts, buf);
	if (buf != 0)
		free(buf);
}
