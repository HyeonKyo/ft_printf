/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_print1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 14:38:33 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/06/20 14:38:34 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	arg_hhn(va_list ap, size_t cnt)
{
	char	*s;

	s = va_arg(ap, char *);
	if (s == 0)
		return ;
	*s = cnt;
}

void	arg_hn(va_list ap, size_t cnt)
{
	short	*s;

	s = va_arg(ap, short *);
	if (s == 0)
		return ;
	*s = cnt;
}

void	arg_ln(va_list ap, size_t cnt)
{
	long	*s;

	s = va_arg(ap, long *);
	if (s == 0)
		return ;
	*s = cnt;
}

void	arg_lln(va_list ap, size_t cnt)
{
	long long	*s;

	s = va_arg(ap, long long *);
	if (s == 0)
		return ;
	*s = cnt;
}

void	arg_n(va_list ap, size_t cnt)
{
	int	*s;

	s = va_arg(ap, int *);
	if (s == 0)
		return ;
	*s = cnt;
}
