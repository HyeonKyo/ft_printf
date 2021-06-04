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

char	*pf_itoa_hex(unsigned long long n, t_opt opts)
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
	while (n)
	{
		buf[--len] = hex[n % 16];
		n = n / 16;
	}
	return (buf);
}

char	*x_pre_task(va_list ap, t_opt *opts, unsigned int *n, int *size)
{
	//length고려 코드 추가해야함.
	char	*buf;

	*n = va_arg(ap, unsigned int);
	if (opts->fg.hash || opts->fg.space || opts->fg.plus || 
    (opts->prec == -3 && n == 0))//경메 출력 조건
		return (0);
	if ((opts->fg.minus && opts->fg.zero) || opts->prec == -2)//0 flag 무시조건.
		opts->fg.zero = 0;
	if (opts->prec > 0)
		opts->fg.minus = 0;
	if (opts->prec > 0)//precision과 width 둘 다 있으면 width무시.
		*size = opts->prec;
	else if (opts->width > 0)
		*size = opts->width;
	buf = pf_itoa_hex((unsigned long long)*n, *opts);
	if (!buf)
		return (0);
	return (buf);
}

void	x_print(va_list ap, t_opt opts, size_t *cnt)
{
	unsigned int    n;
	int		        size;
	char	        *buf;

	n = 0;
	size = 0;
	buf = x_pre_task(ap, &opts, &n, &size);
	if (buf == 0)
		return ;
	*cnt = u_print_case(size, opts, buf);
}
