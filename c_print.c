#include "ft_printf.h"

void	c_print(va_list ap, t_opt opts, size_t *cnt)
{
	char	c;

	if (opts.type == '%')
		c = '%';
	else
		c = va_arg(ap, int);
	//2. width가 0이면 그냥 문자 출력하면 됨.
	if (opts.width == 0)
		*cnt += print_char(c, 1);
	//3. width가 있으면 minus옵션이 있는 경우와 없는 경우로 나뉨.
	else if (opts.fg.minus == 1)
	{
		*cnt += print_char(c, 1);
		*cnt += print_char(' ', opts.width - 1);
	}
	else
	{
		if (opts.type == '%' && opts.fg.zero)
			*cnt += print_char('0', opts.width - 1);
		else
			*cnt += print_char(' ', opts.width - 1);
		*cnt += print_char(c, 1);
	}
}
