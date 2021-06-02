/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_print.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 18:45:47 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/06/02 18:45:49 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	s_print(va_list ap, t_opt opts, size_t *cnt)
{
	char	*s;
    size_t	print_len;
    int		space_len;

	s = va_arg(ap, char *);
	if (opts.prec == -2)
		print_len = 0;
    else if (opts.prec > 0 && opts.prec < (int)ft_strlen(s))
        print_len = opts.prec;
    else
        print_len = ft_strlen(s);
	space_len = opts.width - print_len;
	//출력부분
	if (opts.width == 0 || space_len <= 0)
		*cnt += print_str((char *)s, print_len);
	//3. width가 있으면 minus옵션이 있는 경우와 없는 경우로 나뉨.
	else if (opts.fg.minus)
	{
		*cnt += print_str((char *)s, print_len);
        *cnt += print_char(' ', space_len);
	}
	else
	{
        *cnt += print_char(' ', space_len);
		*cnt += print_str((char *)s, print_len);
	}
}