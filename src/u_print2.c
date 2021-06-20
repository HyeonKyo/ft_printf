/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_print2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 14:49:37 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/06/20 14:49:39 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	u_print_case(int zero_len, int len, char *buf, t_opt opts)
{
	size_t	cnt;
	int		buf_len;

	cnt = 0;
	buf_len = (int)ft_strlen(buf);
	if (buf == 0)
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

	buf_len = (int)ft_strlen(buf);
	zero_len = opts.prec - buf_len;
	len = opts.width - buf_len;
	if (zero_len > 0)
		len -= zero_len;
	return (u_print_case(zero_len, len, buf, opts));
}
/*
** buf_len 숫자 길이
** zero_len prec에 의한 0출력 길이
** len 숫자+0출력 후 남은 공백, 0출력 길이
*/

void			u_print(va_list ap, t_opt opts, size_t *cnt)
{
	t_ull	n;
	char	*buf;

	n = 0;
	buf = u_pre_task(ap, &opts, &n);
	if (buf == 0)
		return ;
	if (opts.prec < 0 && n == 0)
	{
		free(buf);
		buf = 0;
	}
	*cnt += u_print_all(opts, buf);
	if (buf)
		free(buf);
}
