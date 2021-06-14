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

size_t	print_space(t_opt opts, int len)
{
	size_t	cnt;

	cnt = 0;
	if (len > 0)
	{
		if (opts.fg.zero)
			cnt += print_char('0', len);
		else
			cnt += print_char(' ', len);
	}
	return (cnt);
}

size_t	print_deci(t_real num, t_opt opts)
{
	int		i;
	int		n;
	double	tmp;
	int		pre;
	size_t	cnt;

	i = 0;
	cnt = 0;
	tmp = num.deci;
	pre = 0;
	//printf("\n\n");
	while (i < opts.prec)
	{
		tmp *= 10;
		tmp -= (double)(pre * 10);
		//printf("tmp : %.20f\n", tmp);
		if (i++ == opts.prec - 1)
			tmp += 0.5;
		n = (int)tmp;
		cnt += print_char(n + '0', 1);
		pre = n;
	}
	//printf("\n\n");
	return (cnt);
}
//tmp가 맨 처음 10을 곱할 때 뒤의 값이 반올림됨.

size_t	f_print_all(t_real num, t_opt opts, char *i_buf)
{
	size_t	cnt;

	cnt = 0;
	cnt += print_sign(opts, num.sign);
	cnt += print_str(i_buf, ft_strlen(i_buf));
	if (opts.prec > 0)
		cnt += print_char('.', 1);
	cnt += print_deci(num, opts);
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
		cnt += f_print_all(num, opts, i_buf);
		cnt += print_space(opts, len);
	}
	else
	{
		cnt += print_space(opts, len);
		cnt += f_print_all(num, opts, i_buf);
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