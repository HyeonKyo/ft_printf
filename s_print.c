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
    int		print_len;
	int		space_len;

	s = va_arg(ap, char *);
	if (s == 0)
		s = "(null)";
	if (opts.prec < 0)
		print_len = 0;
	else if (opts.prec > 0 && opts.prec < (int)ft_strlen(s))
		print_len = opts.prec;
	else
		print_len = ft_strlen(s);
	space_len = opts.width - print_len;
	//출력부분
	if (space_len > 0 && !opts.fg.minus)
	{
		if (opts.fg.zero)//undefined behavior이나 테스터에 걸림
			*cnt += print_char('0', space_len);
		else
			*cnt += print_char(' ', space_len);
	}
	*cnt += print_str(s, print_len);
	if (space_len > 0 && opts.fg.minus)
        *cnt += print_char(' ', space_len);
}