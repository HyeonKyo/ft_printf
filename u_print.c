#include "ft_printf.h"

char	*u_pre_task(va_list ap, t_opt *opts, unsigned int *n, int *size)
{
	//length고려 코드 추가해야함.
	char	*buf;

	*n = va_arg(ap, unsigned int);
	if (opts->fg.hash || opts->fg.space || opts->fg.plus || 
    (opts->prec == -3 && n == 0))//경메 출력 조건
		return (0);
	if ((opts->fg.minus && opts->fg.zero) || opts->prec == -2)//0 flag 무시조건.
		opts->fg.zero = 0;
	if (opts->prec > 0)
		opts->fg.minus = 0;
	if (opts->prec > 0)//precision과 width 둘 다 있으면 width무시.
		*size = opts->prec;
	else if (opts->width > 0)
		*size = opts->width;
	buf = pf_itoa((long long)*n, *opts);//pf_itoa는 기호 제외하고 숫자만 출력
	if (!buf)
		return (0);
	return (buf);
}
//공백, 부호, 숫자 or 부호 숫자 공백

size_t	print_buf(char *buf)
{
	size_t	cnt;

	cnt = 0;
	write(1, buf, ft_strlen(buf));
	cnt += ft_strlen(buf);
	return (cnt);
}

size_t	u_print_case(unsigned int n, int size, t_opt opts, char *buf)
{
	size_t	cnt;
	int		len;

	cnt = 0;
	len = size - ft_strlen(buf);
	if (len > 0 && opts.fg.minus)
	{
		cnt += print_buf(n, buf, opts);
		if (opts.prec > 0)
			cnt += print_char('0', len);
		else
			cnt += print_char(' ', len);
	}
	else
	{
		if (len > 0)
		{
			if (opts.fg.zero || (opts.prec > 0))
				cnt += print_char('0', len);
			else
				cnt += print_char(' ', len);
		}
		cnt += print_buf(n, buf, opts);
	}
	return (cnt);
}

void	u_print(va_list ap, t_opt opts, size_t *cnt)
{
	unsigned int    n;
	int		        size;
	char	        *buf;

	n = 0;
	size = 0;
	buf = u_pre_task(ap, &opts, &n, &size);
	if (buf == 0)
		return ;
	*cnt = u_print_case(n, size, opts, buf);
}