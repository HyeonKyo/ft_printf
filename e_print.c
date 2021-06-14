#include "ft_printf.h"

void	find_point(t_real *num)
{
	int	n;
	int	cnt;

	n = num->integ;
	cnt = 0;
	while (n > 10)
	{
		n /= 10;
		cnt++;
	}
	num->point = cnt;
}

void	e_div_section(int *bits, t_value val, t_real *num, t_opt opts)
{
	int	i;
	int	n;

	i = 0;
	num->sign = 1;
	if (bits[0])
		num->sign = -1;
	num->integ= (int)val.f;
	find_point(num);
	if (opts.prec < 0)
	{
		n = num->integ;
		while (n >= 100)
			n /= 10;
		if (n / 10 >= 5)
			num->integ += power(10, num->point);
	}
	//소수부분 처리
	take_decimal(bits, num);
	free(bits);
	// printf("\nnum.point : %d\n", num->point);
	// printf("num.integ : %d\n", num->integ);
}

size_t	print_expo(t_real num)
{
	size_t	cnt;
	char	*str;

	str = pf_itoa((long long)num.point);
	if (str == 0)
		return (0);
	cnt = print_str("e+", 2);
	if (num.point < 10)
		cnt += print_char('0', 1);
	cnt += print_str(str, ft_strlen(str));
	free(str);
	return (cnt);
}

size_t	e_print_all(t_real num, t_opt opts, char *i_buf, char *d_buf)
{
	size_t	cnt;

	cnt = 0;
	cnt += print_sign(opts, num.sign);
	cnt += print_char(i_buf[0], 1);
	if (opts.prec >= 0)
	{
		cnt += print_char('.', 1);
		cnt += print_str(i_buf + 1, ft_strlen(i_buf));
		cnt += print_str(d_buf, ft_strlen(d_buf));
	}
	cnt += print_expo(num);
	return (cnt);
}

size_t	e_print_case(t_real num, t_opt opts, char *i_buf, char *d_buf)
{
	int		len;
	size_t	cnt;

	cnt = 0;
	len = opts.width - (ft_strlen(i_buf) + ft_strlen(d_buf) + 5);
	if (opts.fg.plus || opts.fg.space || num.sign < 0)
		len--;
	if (opts.fg.minus)
	{
		cnt += e_print_all(num, opts, i_buf, d_buf);
		cnt += print_space(opts, len);
	}
	else
	{
		cnt += print_space(opts, len);
		cnt += e_print_all(num, opts, i_buf, d_buf);
	}
	return (cnt);
}

void	e_print(va_list ap, t_opt opts, size_t *cnt)
{
	t_value	val;
	t_real	num;
	int		*bits;
	char	*i_buf;
	char	*d_buf;

	ft_memset(&val, 0, sizeof(t_value));
	ft_memset(&num, 0, sizeof(t_real));
	bits = f_pre_tesk(&val, ap, &opts);
	e_div_section(bits, val, &num, opts);
	i_buf = pf_itoa((long long)num.integ);
	d_buf = pf_itoa((long long)(num.deci * power(10, opts.prec - num.point)) + 0.5);
	*cnt += e_print_case(num, opts, i_buf, d_buf);
	free(i_buf);
	free(d_buf);
}