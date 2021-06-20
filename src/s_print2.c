/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_print2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 16:01:17 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/06/20 16:01:18 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	print_wstr(va_list ap, t_opt opts, int len)
{
	int		i;
	size_t	cnt;
	wchar_t	*str;

	str = va_arg(ap, wchar_t *);
	if (str == 0)
		str = L"(null)";
	i = 0;
	cnt = 0;
	if (str[0] == 0 && len == 0 && len < c_case_cnt(str[i], opts))
		return (0);
	while (str[i] && (int)cnt < len)
		cnt += c_case_print(str[i++], opts);
	return (cnt);
}

static size_t	s_print_all(va_list ap, int len, t_opt opts)
{
	size_t	cnt;
	char	*str;

	cnt = 0;
	if (opts.ln.l)
		cnt += print_wstr(ap, opts, len);
	else
	{
		str = va_arg(ap, char *);
		if (str == 0)
			str = "(null)";
		cnt += print_str(str, len);
	}
	return (cnt);
}

void			s_print(va_list ap, t_opt opts, size_t *cnt)
{
	va_list	tmp;
	int		print_len;
	int		space_len;

	va_copy(tmp, ap);
	print_len = get_print_len(tmp, opts);
	space_len = opts.width - print_len;
	if (!opts.fg.minus)
	{
		if (opts.fg.zero)
			*cnt += print_char('0', space_len);
		else
			*cnt += print_char(' ', space_len);
	}
	*cnt += s_print_all(ap, print_len, opts);
	if (opts.fg.minus)
		*cnt += print_char(' ', space_len);
}
/*
** print_len 출력할 문자열 길이
** space_len 공백 출력 길이
** fg_zero : undefined behavior이나 테스터에 걸림
*/
