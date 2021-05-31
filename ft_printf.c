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

void	find_flag(const char *str, t_opt *opts, size_t *i)
{
	char	c;

	c = str[*i];
	if (str[*i] == '-')
		opts->fg.minus = 1;
	else if (str[*i] = '+')
		opts->fg.plus = 1;
	else if (str[*i] == ' ')
		opts->fg.space = 1;
	else if (str[*i] == '0')
		opts->fg.zero = 1;
	else if (str[*i] == '\'')
		opts->fg.apos = 1;
	else if (str[*i] == '#')
		opts->fg.hash = 1;
	else
	{
		opts->fg.none = 1;
		c = 0;
	}
	while (str[*i] == c)
		*(i++);
}

int		pf_atoi(const char *str, t_opt *opts, size_t *i)
{
	unsigned long long	num;

	sign = 1;
	num = 0;
	if (str[*i] == '-')//width or prec가 음수일 때 처리하는 방식이 똑같음.
	{
		opts->width = 0;//prec이 음수일 경우 기존width를 무시함.
		opts->fg.minus = 1;
		i++;
	}
	while (ft_isdigit(str[*i]))
		num = num * 10 + (str[*(i++)] - '0');
	return ((int)num);
	//2. 유효성 검사할 부분이 필요함.
}

void	find_width(const char *str, t_opt *opts, size_t *i)
{
	if (str[i] == '*')
	{
		opts->width = -1;
		i++;
	}
	else
		opts->width = pf_atoi(str, opts, i);
}

void	find_prec(const char *str, t_opt *opts, size_t *i)
{
	if (str[i] == '*')
	{
		opts->prec = -1;
		i++;
	}
	else if (str[*i] == '-')
		opts->width = pf_atoi(str, opts, i);
	else if (ft_isdigit(str[*i]))
		opts->prec = pf_atoi(str, opts, i);
	else
		return ;
}

void	find_length(const char *str, t_opt *opts, size_t *i)
{
	if (str[i] == 'h' && str[i + 1] == 'h')
		opts->ln.hh = 1;
	else if (str[i] == 'l' && str[i + 1] == 'l')
		opts->ln.ll = 1;
	else if (str[i] == 'h')
		opts->ln.h = 1;
	else if (str[i] == 'l')
		opts->ln.l = 1;
	else if (str[i] == 'j')
		opts->ln.j = 1;
	else if (str[i] == 'z')
		opts->ln.z = 1;
	else if (str[i] == 't')
		opts->ln.t = 1;
	else if (str[i] == 'L')
		opts->ln.L = 1;
	else
	{
		opts->ln.none = 1;
		return ;
	}
	if (opts->ln.hh || opts->ln.ll)
		i += 2;
	else
		i++;
}

int		find_type(char c, t_opt *opts)
{
	if (c == 'd' || c = 'i' || c == 'u' || c == 'o' || c == 'x'
	|| c == 'X' || c == 'f' || c == 'F' || c == 'e' || c == 'E'
	|| c == 'g' || c == 'G' || c == 'a' || c == 'A' || c == 'c'
	|| c == 's' || c == 'p' || c == 'n' || c == '%')
	{
		opts->type = c;
		return (1);
	}
	return (0);
}

int		get_opt(const char *str, t_opt *opts, size_t *i) //%뒤의 문자열 주소값을 넣어줌.
{
	//유효성 검사 어떻게 할 지?
	find_flag(str, opts, &i);
	find_width(str, opts, &i);
	if (str[i] == '.')
		find_prec(str, opts, &(++i));
	find_length(str, opts, &i);
	if (!find_type(str[i], opts))
		return (0);
	return (1);
}

void	c_print(va_list ap, t_opt opts)
{
	char	c;

	if (opts.ln.l == 1)
		c = va_arg(ap, wint_t);
	else
		c = va_arg(ap, int);
	if (opts.width == 0)
	{
		write (1, &c, sizeof(c)); //wint_t일 때도 char변수로 받아도 되는지?
		cnt += sizeof(c); //sizeof(c)가 맞는지? int형으로 받았지만 char로 출력하니까?
	if (opts.fg.minus == 1 && opts.width)
	{
		write (1, &c, 1);
		*cnt += opts.width;
	}
	else
	{
		if (opts.width)
			write (1, " ", opts.width - 1);
		write (1, &c, 1);
		*cnt += 1;
	}
}


void	print_arg(va_list ap, t_opt opts, size_t *cnt)
{
	if (opts.type == 'c')
		c_print(ap, opts, &cnt);
	else if (opts.type == 'd')
		d_print(ap, opts, &cnt);
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
	ft_memset(&opts, 0, sizeof(t_opt));
	while (str[i])
	{
		if (str[i] == '%')
		{
			//구조체에 각 옵션 값들 넣어줌.
			get_opt(str, &opts, &i);
			//가변인자 하나씩 받아서 *인 곳 바꿔주기
			if (opts->width == -1) // = *일 떄 width에 넣어줄 값
			{
				opts->width = va_arg(ap, int); //음수일 경우도 고려해줘야함.
				if (opts->width < 0)
				{
					opts.fg.minus = 1;
					opts->width *= -1;
				}
			}
			if (opts->prec == -1)
			{
				opts->prec = va_arg(ap, int);
				if (opts->prec < 0)
				{
					opts.fg.minus = 1;
					opts->prec *= -1;
				}
			}
			//각 옵션의 조합 고려해서 출력
			//printfuc(opts, ap??); // type에 맞는 자료형으로 va_arg를 통해 받아야함.
			//cnt더해줌
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
