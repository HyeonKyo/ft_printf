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

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_memset(void *ptr, int nue, size_t num)
{
	char	*str;
	size_t	i;

	i = 0;
	str = ptr;
	while (i < num)
		str[i++] = nue;
	return (ptr);
}

int		ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

void	c_print(va_list ap, t_opt opts, size_t *cnt)
{
	wint_t	c;
	int		i;

	i = 0;
	//1. length에 맞는 변수로 가변인자값 받음.
	if (opts.ln.l == 1)
		c = va_arg(ap, wint_t);
	else
		c = va_arg(ap, int);
	//2. width가 0이면 그냥 문자 출력하면 됨.
	if (opts.width == 0)
	{
		write (1, &c, sizeof(c));
		cnt += sizeof(c); //sizeof(c)가 맞는지? int형으로 받았지만 char로 출력하니까?
		return ;
	}
	//3. width가 있으면 minus옵션이 있는 경우와 없는 경우로 나뉨.
	else if (opts.fg.minus == 1)
	{
		write (1, &c, sizeof(c));
		while (i++ < opts.width - 1)
			write (1, " ", 1);
	}
	else
	{
		while (i++ < opts.width - 1)
			write (1, " ", 1);
		write (1, &c, 1);
	}
	*cnt += opts.width;
}

void	print_arg(va_list ap, t_opt opts, size_t *cnt)
{
	if (opts.type == 'c')
		c_print(ap, opts, cnt);
	else if (opts.type == 'd')
		d_print(ap, opts, cnt);
	else if (opts.type == 'i')
		d_print(ap, opts, cnt);
	else if (opts.type == 'u')
		u_print(ap, opts, cnt);
	else if (opts.type == 'x')
		x_print(ap, opts, cnt);
	else if (opts.type == 'X')
		x_print(ap, opts, cnt);
	else if (opts.type == 's')
		s_print(ap, opts, cnt);
	else if (opts.type == 'p')
		p_print(ap, opts, cnt);
	//....
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
			//구조체에 각 옵션 값들 넣어줌.
			ft_memset(&opts, 0, sizeof(t_opt));
			get_opt(str, &opts, &i);
			//printf("\ncnt2 : %ld\n", cnt);
			//printf("flag.minus1 : %d\n", opts.fg.minus);
			//printf("flag.width1 : %d\n", opts.width);
			//printf("flag.prec1 : %d\n", opts.prec);
			//printf("flag.type : %c\n", opts.type);
			//가변인자 하나씩 받아서 *인 곳 바꿔주기
			if (opts.width == -1) // = *일 떄 width에 넣어줄 값
			{
				opts.width = va_arg(ap, int); //음수일 경우도 고려해줘야함.
				if (opts.width < 0)
				{
					opts.fg.minus = 1;
					opts.width *= -1;
				}
			}
			if (opts.prec == -1)
			{
				opts.prec = va_arg(ap, int);
				if (opts.prec < 0)
				{
					opts.fg.minus = 1;
					opts.prec *= -1;
				}
			}
			//printf("\nflag.minus2 : %d\n", opts.fg.minus);
			//printf("flag.width2 : %d\n", opts.width);
			//printf("flag.prec2 : %d\n", opts.prec);
			//각 옵션의 조합 고려해서 출력
			print_arg(ap, opts, &cnt);
			//printf("cnt1 : %ld\n", cnt);
		}
		else
		{
			write(1, str + i, 1);
			cnt++;
		}
		i++;
	}
	va_end(ap);
	return (cnt);
}

int main()
{
	char	*s = "abcde";

	ft_printf("[%p]\n", s);
	ft_printf("[%3p]\n", s);
	ft_printf("[%20p]\n", s);
	ft_printf("[%-20p]\n", s);
	ft_printf("[%20.3p]\n", s);
	ft_printf("\n----------------\n\n");
	printf("[%p]\n", s);
	printf("[%3p]\n", s);
	printf("[%20p]\n", s);
	printf("[%-20p]\n", s);
	printf("[%20.3p]\n", s);

	return (0);
}