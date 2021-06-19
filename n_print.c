#include "ft_printf.h"

void	arg_hhn(va_list ap, size_t cnt)
{
	char	*s;

	s = va_arg(ap, char *);
	if (s == 0)
		return ;
	*s = cnt;
}

void	arg_hn(va_list ap, size_t cnt)
{
	short	*s;

	s = va_arg(ap, short *);
	if (s == 0)
		return ;
	*s = cnt;
}

void	arg_ln(va_list ap, size_t cnt)
{
	long	*s;

	s = va_arg(ap, long *);
	if (s == 0)
		return ;
	*s = cnt;
}

void	arg_lln(va_list ap, size_t cnt)
{
	long long	*s;

	s = va_arg(ap, long long *);
	if (s == 0)
		return ;
	*s = cnt;
}

void	arg_n(va_list ap, size_t cnt)
{
	int	*s;

	s = va_arg(ap, int *);
	if (s == 0)
		return ;
	*s = cnt;
}

void	n_print(va_list ap, t_opt opts, size_t *cnt)
{
	if (opts.ln.hh)
		arg_hhn(ap, *cnt);
	if (opts.ln.h)
		arg_hn(ap, *cnt);
	if (opts.ln.l)
		arg_ln(ap, *cnt);
	if (opts.ln.ll)
		arg_lln(ap, *cnt);
	arg_n(ap, *cnt);
}