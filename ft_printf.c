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

void	get_star(va_list ap, t_opt *opts)
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

void	print_arg(va_list ap, t_opt opts, size_t *cnt)
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
}

int		ft_printf(const char *str, ...)
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

//구조체에 각 옵션 값들 넣어줌.
//가변인자 하나씩 받아서 *인 곳 바꿔주기
//각 옵션의 조합 고려해서 출력

// int main()
// {
// 	ft_printf("[%2.9p]", 1234);
// 	ft_printf("\n----------------\n\n");
// 	printf("[%2.9p]", 1234);


// 	return (0);
// }