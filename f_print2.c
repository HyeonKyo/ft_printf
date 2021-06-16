/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_print2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 16:50:48 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/06/14 16:50:49 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	print_space(t_opt opts, t_real num, int len)
{
	size_t	cnt;

	cnt = 0;
	if (len > 0)
	{
		if (opts.fg.zero)
		{
			cnt += print_sign(opts, num.sign);
			cnt += print_char('0', len);
		}
		else
			cnt += print_char(' ', len);
	}
	return (cnt);
}

void	round_num(t_real *num, int len)
{
	int	n;

	if (len < 0)
		return ;
	if ((n = pf_get_size(num->deci.high)) > len + 1)
		num->deci.high += power(10, n - len - 1) * 0.5;
	else
	{
		len -= n - 1;
		if ((n = pf_get_size(num->deci.mid)) > len)
			num->deci.mid += power(10, n - len) * 0.5;
		else
		{
			len -= n;
			if ((n = pf_get_size(num->deci.mid)) > len)
				num->deci.low += power(10, n - len) * 0.5;
		}
	}
}

size_t	print_deci(t_real num, int len)//len = precision
{
	char	*high_buf;
	char	*mid_buf;
	char	*low_buf;
	int		print_len;
	size_t	cnt;

	cnt = 0;
	round_num(&num, len);
	high_buf = pf_itoa((num.deci.high));
	mid_buf = pf_itoa((num.deci.mid));
	low_buf = pf_itoa((num.deci.low));
	print_len = len;
	cnt = print_str(high_buf + 1, len);
	if (cnt < len)
	{
		print_len = len - cnt;
		cnt += print_str(mid_buf, print_len);
	}
	if (cnt < len)
	{
		print_len = len - cnt;
		cnt += print_str(low_buf, print_len);
	}
	return (cnt);
}
//tmp가 맨 처음 10을 곱할 때 뒤의 값이 반올림됨.

size_t	f_print_all(t_real num, t_opt opts, char *i_buf, int len)
{
	size_t	cnt;

	cnt = 0;
	if (!(opts.fg.zero && len > 0))
		cnt += print_sign(opts, num.sign);
	cnt += print_str(i_buf, ft_strlen(i_buf));
	if (opts.prec > 0)
		cnt += print_char('.', 1);
	cnt += print_deci(num, opts.prec);
	return (cnt);
}

size_t	f_print_case(t_real num, t_opt opts, char *i_buf)
{
	int		len;
	int		dec_len;
	size_t	cnt;

	cnt = 0;
	dec_len = opts.prec + 1;
	if (dec_len < 0)
		dec_len = 0;
	len = opts.width - (ft_strlen(i_buf) + dec_len);
	if (opts.fg.plus || opts.fg.space || num.sign < 0)
		len--;
	if (opts.fg.minus)
	{
		cnt += f_print_all(num, opts, i_buf, len);
		cnt += print_space(opts, num, len);
	}
	else
	{
		cnt += print_space(opts, num, len);
		cnt += f_print_all(num, opts, i_buf, len);
	}
	return (cnt);
}

void	f_print(va_list ap, t_opt opts, size_t *cnt)
{
	t_value	val;
	t_real	num;
	int		*bits;
	char	*i_buf;

	ft_memset(&val, 0, sizeof(t_value));
	ft_memset(&num, 0, sizeof(t_real));
	bits = f_pre_tesk(&val, ap, &opts);
	f_div_section(bits, val, &num, opts);
	i_buf = pf_itoa((long long)num.integ);
	*cnt += f_print_case(num, opts, i_buf);
	free(i_buf);
}