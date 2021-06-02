/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 15:43:48 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/06/02 15:43:49 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_sign(t_opt opts, int n)
{
	if (opts.fg.plus && n > 0)
		write(1, "+", 1);
	else if (opts.fg.space && n > 0)
		write(1, " ", 1);
	else if (n < 0)
		write(1, "-", 1);
	else
		return (0);
	return (1);
}

char	*pf_itoa_hex(long long n, t_opt opts)
{
	int		len;
	char	*buf;
	char	*hex;

	len = get_size_based(n, 16);
	buf = (char *)malloc((len + 1) * sizeof(char));
	if (buf == 0)
		return (0);
	buf[len] = 0;
	if (opts.type == 'x')
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