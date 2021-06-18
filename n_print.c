#include "ft_printf.h"

long long	*get_arg_n(va_list ap, t_opt opts)
{
	if (opts.ln.hh)
		return ((long long *)va_arg(ap, char *));
	if (opts.ln.h)
		return ((long long *)va_arg(ap, short *));
	if (opts.ln.l)
		return ((long long *)va_arg(ap, long *));
	if (opts.ln.ll)
		return (va_arg(ap, long long *));
	return ((long long *)va_arg(ap, int *));
}

void	n_print(va_list ap, t_opt opts, size_t *cnt)
{
	long long	*n;

	n = get_arg_n(ap, opts);
	if (n == 0)
		return ;
	*n = *cnt;
}