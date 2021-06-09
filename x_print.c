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
	if (n == 0)
		buf[0] = '0';
	while (n)
	{
		buf[--len] = hex[n % 16];
		n = n / 16;
	}
	return (buf);
}

char	*x_pre_task(va_list ap, t_opt *opts, unsigned int *n)
{
	char	*buf;

	*n = va_arg(ap, unsigned int);
	if (opts->fg.hash || opts->fg.space || opts->fg.plus || 
    (opts->prec == -3 && n == 0))//경메 출력 조건
		return (0);
	if ((opts->fg.minus && opts->fg.zero) || opts->prec != 0)//0 flag 무시조건.
		opts->fg.zero = 0;
	buf = pf_itoa_hex((unsigned long long)*n, *opts);
	if (!buf)
		return (0);
	return (buf);
}

void	x_print(va_list ap, t_opt opts, size_t *cnt)
{
	unsigned int    n;
	char	        *buf;

	n = 0;
	buf = x_pre_task(ap, &opts, &n);
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
