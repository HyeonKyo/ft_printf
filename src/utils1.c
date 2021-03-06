/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 15:43:44 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/06/02 15:43:45 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			print_char(char c, int len)
{
	int	i;

	i = 0;
	if (len <= 0)
		return (0);
	while (i++ < len)
		write(1, &c, 1);
	return (len);
}

int			pf_atoi(const char *str, size_t *i)
{
	unsigned long long	num;

	num = 0;
	while (ft_isdigit(str[*i]))
		num = num * 10 + (str[(*i)++] - '0');
	return ((int)num);
}

static int	pf_get_size(long long n)
{
	int	size;

	size = 0;
	if (n == 0)
		size = 1;
	while (n)
	{
		size++;
		n = n / 10;
	}
	return (size);
}

int			pf_absol_n(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

char		*pf_itoa(long long n)
{
	int		len;
	char	*buf;

	len = pf_get_size(n);
	buf = (char *)malloc((len + 1) * sizeof(char));
	if (buf == 0)
		return (0);
	buf[len] = 0;
	if (n == 0)
		buf[0] = '0';
	while (n)
	{
		buf[--len] = pf_absol_n(n % 10) + '0';
		n = n / 10;
	}
	return (buf);
}
