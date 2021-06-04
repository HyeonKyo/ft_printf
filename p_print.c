#include "ft_printf.h"

char	*p_pre_task(va_list ap, t_opt *opts, unsigned long long *n, int *size)
{
	void	*buf;

	*n = (unsigned long long)va_arg(ap, void *);
	if (opts->fg.hash || opts->fg.plus || opts->fg.space || opts->fg.zero
	|| opts->fg.apos || opts->prec != 0)//경메 출력 조건
		return (0);
	if (opts->width > 0)
		*size = opts->width;
	buf = pf_itoa_hex(*n, *opts);//pf_itoa는 기호 제외하고 숫자만 출력
	if (!buf)
		return (0);
	return (buf);
}

size_t	print_hex_addr(char *buf)
{
	write(1, "0x", 2);
	print_str(buf, ft_strlen(buf));
	return (2 + ft_strlen(buf));
}

size_t	p_print_case(int print_size, t_opt opts, char *buf)
{
	size_t	cnt;
	int		len;

	cnt = 0;
	len = print_size - (ft_strlen(buf) + 2);
	if (len > 0 && !opts.fg.minus)
	{
		cnt += print_char(' ', len);
		cnt += print_hex_addr(buf);
	}
	else
	{
		print_hex_addr(buf);
		if (opts.fg.minus)
			print_char(' ', len);
	}
	return (cnt);
}

void	p_print(va_list ap, t_opt opts, size_t *cnt)
{
	unsigned long long	n;
	int					size;
	char				*buf;

	n = 0;
	size = 0;
	buf = p_pre_task(ap, &opts, &n, &size);
	if (buf == 0)
		return ;
	*cnt = p_print_case(size, opts, buf);
}