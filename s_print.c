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

wchar_t	*get_arg_s(va_list ap, t_opt opts)
{
	if (opts.ln.l)
		return (va_arg(ap, wchar_t *));
	return ((wchar_t *)va_arg(ap, char *));
}

int		pf_wstrlen(wchar_t *str)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	if (str == 0)
		return (0);
	while (str[i])
		cnt += 1 * c_case_cnt(str[i++]);
	return (cnt);
}

size_t	print_wstr(va_list ap, int len)
{
	int		i;
	size_t	cnt;
	wchar_t	*str;

	str = va_arg(ap, wchar_t *);
	if (str == 0)
		str = L"(null)";
	i = 0;
	cnt = 0;
	if (str[0] == 0 && len == 0 && len < c_case_cnt(str[i]))
		return (0);
	while (str[i] && cnt < len)
		cnt += c_case_print(str[i++]);
	return (cnt);
}

size_t	s_print_all(va_list ap, int len, t_opt opts)
{
	size_t	cnt;
	char	*str;

	cnt = 0;
	if (opts.ln.l)
		cnt += print_wstr(ap, len);
	else
	{
		str = va_arg(ap, char *);
		if (str == 0)
			str = "(null)";
		cnt += print_str(str, len);
	}
	return (cnt);
}

void	s_print(va_list ap, t_opt opts, size_t *cnt)
{
	wchar_t	*s;
	va_list	tmp;
    int		print_len;
	int		space_len;

	va_copy(tmp, ap);
	s = get_arg_s(tmp, opts);
	if (s == 0)
		s = L"(null)";
	if (opts.prec < c_case_cnt(s[0]))//출력할 문자열 길이 = print_len
		print_len = 0;
	else if (opts.prec > 0 && opts.prec < pf_wstrlen(s))
		print_len = opts.prec;
	else
		print_len = pf_wstrlen(s);
	space_len = opts.width - print_len;//공백 출력 길이
	if (!opts.fg.minus)
	{
		if (opts.fg.zero)//undefined behavior이나 테스터에 걸림
			*cnt += print_char('0', space_len);
		else
			*cnt += print_char(' ', space_len);
	}
	*cnt += s_print_all(ap, print_len, opts);//출력할 때 ap를 받아서 출력.
	if (opts.fg.minus)
        *cnt += print_char(' ', space_len);
}