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

size_t	print_deci(t_real num, int len)
{
	int		i;
	int		n;
	double	tmp;
	int		pre;
	size_t	cnt;

	i = 0;
	cnt = 0;
	tmp = num.deci - (double)num.integ;
	pre = 0;
	//출력 부분
	while (i < len)
	{
		tmp *= 10;
		tmp -= (double)(pre * 10);
		n = (int)tmp;
		cnt += print_char(n + '0', 1);
		pre = n;
		i++;
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
	dec_len = opts.prec + 1;//1은 소수점
	if (dec_len < 0)
		dec_len = 0;
	len = opts.width - (ft_strlen(i_buf) + dec_len);//공백길이
	if (opts.fg.plus || opts.fg.space || num.sign < 0)//공백 - 부호
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