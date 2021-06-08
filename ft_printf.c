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

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

void	*ft_memset(void *ptr, int value, size_t num)
{
	char	*str;
	size_t	i;

	i = 0;
	str = ptr;
	while (i < num)
		str[i++] = value;
	return (ptr);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (str == 0)
		return (0);
	while (str[i])
		i++;
	return (i);
}

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
	else if (opts.type == '%')
		c_print(ap, opts, cnt);
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
			if (!get_opt(str, &opts, &i))
				return (cnt);
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
					opts.prec = 0;
				else if (opts.prec == 0)
					opts.prec = -3;
			}
			//각 옵션의 조합 고려해서 출력
			print_arg(ap, opts, &cnt);
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

// int main()
// {
// 	int d = -135;
// 	int n = -12;

// 	ft_printf("[%-4.3d]\n", d);
// 	ft_printf("[%-4.4d]\n", d);
// 	ft_printf("[%-4.d]\n", n);
// 	ft_printf("\n----------------\n\n");
// 	printf("[%-4.3d]\n", d);
// 	printf("[%-4.4d]\n", d);
// 	printf("[%-4.d]\n", n);

// 	return (0);
// }