
#include "ft_printf.h"

static char		*d_pre_task(va_list ap, t_opt *opts, int *n)
{
	char	*buf;

	*n = va_arg(ap, int);
	if (opts->fg.hash)//경메 출력 조건
		return (0);
	if ((opts->fg.minus && opts->fg.zero) || opts->prec != 0)//0 flag 무시조건.
		opts->fg.zero = 0;
	buf = pf_itoa(*n);//pf_itoa는 기호 제외하고 숫자만 출력
	if (!buf)
		return (0);
	return (buf);
}

static size_t	zero_or_space(int n, int space_len, t_opt opts, int *flag)
{
	size_t	cnt;

	if (space_len <= 0)
		return (0);
	cnt = 0;
	if (check_sign(opts, n))
		*flag = 1;
	if (opts.fg.zero)
	{
		cnt = print_sign(opts, n);
		cnt += print_char('0', space_len);
	}
	else
	{
		cnt += print_char(' ', space_len);
		if (!opts.fg.minus && !(opts.prec < 0 && n == 0))
			cnt += print_sign(opts, n);
	}
	return (cnt);
}

static size_t	print_digit(int n, t_opt opts, char *buf, int flag)
{
	size_t	cnt;
	int		buf_len;
	int		prec_len;

	cnt = 0;
	if (n == 0 && opts.prec < 0)
		return (print_sign(opts, n));
	buf_len = ft_strlen(buf);
	prec_len = opts.prec - buf_len;
	if (flag == 0)
		cnt = print_sign(opts, n);
	if (prec_len > 0)
		cnt += print_char('0', prec_len);
	cnt += print_str(buf, buf_len);
	return (cnt);
}


static size_t	d_print_all(int n, t_opt opts, char *buf)
{
	size_t	cnt;
	int		buf_len;
    int     print_len;
    int     space_len;
	int		flag;

	cnt = 0;
	flag = 0;
	buf_len = (int)ft_strlen(buf);
	print_len = buf_len;
    if (opts.prec > buf_len)
        print_len = opts.prec;
    else if (opts.prec < 0 && n == 0)
        print_len = 0;
    space_len = opts.width - print_len - check_sign(opts, n);
    if (!opts.fg.minus)
        cnt += zero_or_space(n, space_len, opts, &flag);
	cnt += print_digit(n, opts, buf, flag);
    if (opts.fg.minus)
        cnt += zero_or_space(n, space_len, opts, &flag);
	return (cnt);
}

void			d_print(va_list ap, t_opt opts, size_t *cnt)
{
	int		n;
	char	*buf;

	n = 0;
	buf = d_pre_task(ap, &opts, &n);
	if (buf == 0)
		return ;
	*cnt += d_print_all(n, opts, buf);
	if (buf)
		free(buf);
}
