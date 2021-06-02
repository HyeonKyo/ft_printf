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

int		print_char(char c, int len)
{
	int	i;

	i = 0;
	while (i++ < len)
		write(1, &c, 1);
	return (len);
}

int		pf_atoi(const char *str, t_opt *opts, size_t *i)
{
	unsigned long long	num;

	num = 0;
	if (str[*i] == '-')//width or prec가 음수일 때 처리하는 방식이 똑같음.
	{
		opts->width = 0;//prec이 음수일 경우 기존width를 무시함.
		opts->fg.minus = 1;
		opts->fg.none = 0;//만약 none이면 0으로 만들어줌.
		i++;
	}
	while (ft_isdigit(str[*i]))
		num = num * 10 + (str[(*i)++] - '0');
	return ((int)num);
	//1. 유효성 검사할 부분이 필요함.
}

int		get_size_based(long long n, int base)
{
	int	size;

	size = 0;
	while (n)
	{
		size++;
		n = n / base;
	}
	return (size);
}

size_t	absol_n(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

char	*pf_itoa(long long n)
{
	int		len;
	char	*buf;

	len = get_size_based(n, 10);
	buf = (char *)malloc((len + 1) * sizeof(char));
	if (buf == 0)
		return (0);
	buf[len] = 0;
	while (n)
	{
		buf[--len] = absol_n(n % 10) + '0';
		n = n / 10;
	}
	return (buf);
}