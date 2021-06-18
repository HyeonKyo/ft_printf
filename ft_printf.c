/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 13:55:49 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/05/31 18:52:41 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	get_star(va_list ap, t_opt *opts)
{
	if (opts->width == -1) // = *일 떄 width에 넣어줄 값
	{
		opts->width = va_arg(ap, int); //음수일 경우도 고려해줘야함.
		if (opts->width < 0)
		{
			opts->fg.minus = 1;
			opts->width *= -1;
		}
	}
	if (opts->prec == -1)
	{
		opts->prec = va_arg(ap, int);
		if (opts->prec < 0)
			opts->prec = 0;
		else if (opts->prec == 0)
			opts->prec = -3;
	}
}

static void	print_arg(va_list ap, t_opt opts, size_t *cnt)
{
	if (opts.type == 'c' || opts.type == '%')
		c_print(ap, opts, cnt);
	else if (opts.type == 'd' || opts.type == 'i')
		d_print(ap, opts, cnt);
	else if (opts.type == 'u')
		u_print(ap, opts, cnt);
	else if (opts.type == 'x' || opts.type == 'X')
		x_print(ap, opts, cnt);
	else if (opts.type == 's')
		s_print(ap, opts, cnt);
	else if (opts.type == 'p')
		p_print(ap, opts, cnt);
	else if (opts.type == 'f')
		f_print(ap, opts, cnt);
	else if (opts.type == 'e')
		e_print(ap, opts, cnt);
	else if (opts.type == 'n')
		n_print(ap, opts, cnt);
}

int			ft_printf(const char *str, ...)
{
	va_list	ap;
	t_opt	opts;
	size_t	i;
	size_t	cnt;

	i = 0;
	cnt = 0;
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			ft_memset(&opts, 0, sizeof(t_opt));
			if (!get_opt(str, &opts, &i))
				return (cnt);
			get_star(ap, &opts);
			print_arg(ap, opts, &cnt);
		}
		else
			cnt += print_char(str[i], 1);
		i++;
	}
	va_end(ap);
	return (cnt);
}

int main()
{
	setbuf(stdout, NULL);
	setlocale(LC_ALL, "en_US.UTF-8");
	wchar_t	*s = 0;
	char	*s2 = 0;
	unsigned long long x = 1234;
	
	
	ft_printf("[%.0x]\n", 0);
	ft_printf("[%hx]\n", x);
	ft_printf("[%hhx]\n", x);
	ft_printf("[%#10.6lx]\n", (unsigned long)x);
	ft_printf("[%#040llx]\n", x);
	ft_printf("\n----------------\n\n");
	printf("[%#10.0x]\n", 0);
	printf("[%hx]\n", x);
	printf("[%hhx]\n", x);
	printf("[%#10.6lx]\n", (unsigned long)x);
	printf("[%#040llx]\n", x);


	return (0);
}