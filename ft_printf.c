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
#include <stdio.h>

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	print_char(char c, int len)
{
	int	i;

	i = 0;
	while (i++ < len)
		write(1, &c, 1);
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

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int		find_flag(const char *str, t_opt *opts, size_t *i)
{
	char	c;

	if (str[*i] == '-')
		opts->fg.minus = 1;
	else if (str[*i] == '+')
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
		opts->fg.none = 1;//flag가 없는 경우.
		return (0);
	}
	if (opts->fg.minus && opts->fg.zero)//경메가 뜨는 flag조합.
		return (-1);
	return (1);
}

int		pf_atoi(const char *str, t_opt *opts, size_t *i)
{
	unsigned long long	num;

	num = 0;
	if (str[*i] == '-')//width or prec가 음수일 때 처리하는 방식이 똑같음.
	{
		opts->width = 0;//prec이 음수일 경우 기존width를 무시함.
		opts->fg.minus = 1;
		opts->fg.none = 0;//만약 none이면 0으로 만들어줌.
		i++;
	}
	while (ft_isdigit(str[*i]))
		num = num * 10 + (str[(*i)++] - '0');
	return ((int)num);
	//1. 유효성 검사할 부분이 필요함.
}

void	find_width(const char *str, t_opt *opts, size_t *i)
{
	if (str[*i] == '*')
	{
		opts->width = -1;
		(*i)++;
	}
	else
		opts->width = pf_atoi(str, opts, i);
}

void	find_prec(const char *str, t_opt *opts, size_t *i)
{
	if (str[*i] == '*')
	{
		opts->prec = -1;
		(*i)++;
	}
	else if (str[*i] == '-')
		opts->width = pf_atoi(str, opts, i);
	else if (ft_isdigit(str[*i]))
	{
		opts->prec = pf_atoi(str, opts, i);
		if (opts->prec == 0)
			opts->prec = -3; //.0인경우
	}
	else
		opts->prec = -2; //.만 있는 경우
}

void	find_length(const char *str, t_opt *opts, size_t *i)
{
	if (str[*i] == 'h' && str[*i + 1] == 'h')
		opts->ln.hh = 1;
	else if (str[*i] == 'l' && str[*i + 1] == 'l')
		opts->ln.ll = 1;
	else if (str[*i] == 'h')
		opts->ln.h = 1;
	else if (str[*i] == 'l')
		opts->ln.l = 1;
	else if (str[*i] == 'j')
		opts->ln.j = 1;
	else if (str[*i] == 'z')
		opts->ln.z = 1;
	else if (str[*i] == 't')
		opts->ln.t = 1;
	else if (str[*i] == 'L')
		opts->ln.L = 1;
	else
	{
		opts->ln.none = 1;
		return ;
	}
	if (opts->ln.hh || opts->ln.ll)
		*i += 2;
	else
		(*i)++;
}

int		find_type(char c, t_opt *opts)
{
	if (c == 'd' || c == 'i' || c == 'u' || c == 'o' || c == 'x'
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
	int	ret;
	//유효성 검사 어떻게 할 지?
	while ((ret = find_flag(str, opts, i)) > 0)
		(*i)++;
	if (ret == -1)
		return (0); //flag가 -와 0이 있는 경우의 에러상황(기존 함수는 경고메시지 출력 후 0옵션 무시)
	find_width(str, opts, i);
	if (str[*i] == '.')
	{
		(*i)++;
		find_prec(str, opts, i);
	}
	find_length(str, opts, i);
	if (!find_type(str[*i], opts))
		return (0);//서식지정자가 없는 에러상황
	return (1);
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
//--------------------------

int		get_size(int n)
{
	int	size;

	size = 0;
	while (n)
	{
		size++;
		n = n / 10;
	}
	return (size);
}

size_t		absol_n(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

char		*pf_itoa(int n, t_opt opts)
{
	int		len;
	char	*buf;

	len = get_size(n);
	buf = (char *)malloc((len + 1) * sizeof(char));
	if (buf == 0)
		return (0);
	buf[len] = 0;
	while (n)
	{
		buf[--len] = absol_n(n % 10) + '0';
		n = n / 10;
	}
	return (buf);
}

void	print_sign(t_opt opts, int n)
{
	if (opts.fg.plus && n > 0)
		write(1, "+", 1);
	else if (opts.fg.space && n > 0)
		write(1, " ", 1);
	else if (n < 0)
		write(1, "-", 1);
}

void	d_print(va_list ap, t_opt opts, size_t *cnt)
{
	int		i;
	int		n;
	int		size;
	int		len;
	int		sign;
	char	*buf;
	
	i = 0;
	size = 0;
	sign = 1;
	n = va_arg(ap, int);
	if (opts.fg.hash || (opts.prec == -3 && n == 0))
		return ;
	if ((opts.fg.minus && opts.fg.zero) || opts.prec == -2)
		opts.fg.zero = 0;
	//length는 나중에 고려
	buf = pf_itoa(n, opts);//itoa는 기호 제외하고 출력
	len = ft_strlen(buf);
	if (opts.prec > 0)
		size = opts.prec;
	else if (opts.width > 0)
		size = opts.width;
	if (len >= size) //width나 precision의 영향이 없는 경우
	{
		//정상출력
		print_sign(opts, n);
		write (1, buf, ft_strlen(buf));
		*cnt += ft_strlen(buf);
	}
	else //width or precision에 의한 출력
	{
		// prec에 의한 출력(.n인 경우 => width 무시)
		if (opts.prec > 0)
		{
			// 0옵션에 관계없이 0이 기본옵션(-옵션있어도 무시)
			print_sign(opts, n);
			print_char('0', size - len);
			write(1, buf, len);
			*cnt += size;
			if (sign)
				(*cnt)++;
		}
		else //1. width에 의한 출력
		{
			//기호 포함 len 조정
			if (opts.fg.plus || n < 0)
				len++;
			if (opts.fg.minus)//좌측 정렬 시 0무시
			{
				print_sign(opts, n);
				write(1, buf, ft_strlen(buf));
				print_char(' ', size - len);
			}
			else
			{
				if (opts.fg.zero)
				{
					print_sign(opts, n);
					print_char('0', size - len);
				}
				else
				{
					print_char(' ', size - len);
					print_sign(opts, n);
				}
				write(1, buf, ft_strlen(buf));
			}
			*cnt += size;
		}
	}
}
//-------------------------------------

void	print_arg(va_list ap, t_opt opts, size_t *cnt)
{
	if (opts.type == 'c')
		c_print(ap, opts, cnt);
	else if (opts.type == 'd')
		d_print(ap, opts, cnt);
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
	int	cnt;

	ft_printf("[%- 3d]\n", 1000);
	ft_printf("[%- 10d]\n", 1000);
	ft_printf("------------\n");
	ft_printf("[%d]\n", -42);
	ft_printf("[%d]\n", -052);
	ft_printf("[%d]\n", -0x2a);
	ft_printf("[%d]\n", -0x2A);
	ft_printf("------------\n");
	return (0);
}