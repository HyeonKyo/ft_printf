/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_print1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 16:03:02 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/06/20 16:03:03 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_wstrlen(wchar_t *str, t_opt opts)
{
	int	cnt;

	cnt = 0;
	if (str == 0)
		return (0);
	while (str[cnt])
		cnt += 1 * c_case_cnt(str[cnt], opts);
	return (cnt);
}

int		case1_print_len(va_list ap, t_opt opts)
{
	wchar_t	*s1;
	int		print_len;

	s1 = va_arg(ap, wchar_t *);
	if (s1 == 0)
		s1 = L"(null)";
	if (opts.prec > 0 && opts.prec < pf_wstrlen(s1, opts))
		print_len = opts.prec;
	else if (opts.prec < c_case_cnt(s1[0], opts))
		print_len = 0;
	else
		print_len = pf_wstrlen(s1, opts);
	return (print_len);
}

int		case2_print_len(va_list ap, t_opt opts)
{
	char	*s2;
	int		print_len;

	s2 = va_arg(ap, char *);
	if (s2 == 0)
		s2 = "(null)";
	if (opts.prec > 0 && opts.prec < (int)ft_strlen(s2))
		print_len = opts.prec;
	else if (opts.prec < 0)
		print_len = 0;
	else
		print_len = ft_strlen(s2);
	return (print_len);
}

int		get_print_len(va_list ap, t_opt opts)
{
	if (opts.ln.l)
		return (case1_print_len(ap, opts));
	else
		return (case2_print_len(ap, opts));
}
