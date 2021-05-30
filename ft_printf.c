#include "ft_printf.h"

int		find_flag(char c, t_opt *opts)
{
	if (c == '-' || c = '+' || c == ' ' || c == '0' ||
	c == '\'' || c == '#')
	{
		opts->flag = c;
		return (1);
	}
	return (0);
}

int		pf_atoi(const char *str, t_opt *opts)
{
	int	i;
	int	j;
	int	sign;
	int	num;

	i = 0;
	j = 0;
	sign = 1;
	num = 0;
	if (str[i] == '-')//width에 음수일 때 처리 방법 정하기
	{
		sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		num = num * 10 + (str[i++] - '0');
	opts->width = num;
	//1. sign이 -일 경우 flag에 영향을 주므로 연결시키는 구성이 필요함.
	//2. 유효성 검사할 부분이 필요함.
	return (i); //수정 필요
}

int		find_width(const char *str, t_opt *opts)
{
	int	i;
	//1. width가 *이면 가변인자에 정수값 있는지 확인 후 넣어줌
	//2. width위치의 문자가 정수이면 atoi처럼 계속 정수를 받아서 int로 변환해서 저장.
	//3. 유효성 검사해서 리턴 값 조정해야 함. (if (ft_isdigit)으로하면?)
	i = pf_atoi(str, opts);
	return (i);
	return (0);
}

int		find_prec(char c, t_opt *opts)
{
	if (ft_isdigit(c))
	{
		opts->prec = c - '0';
		return (1);
	}
	return (0);
}

int		find_length(const char *str, t_opt *opts)
{
	if ((*str == 'h' && *(str + 1) == 'h') || (*str == 'l' && *(str + 1) == 'l'))
	{
		ft_strlcpy(opts->length, str, 3);
		return (2);
	}
	else if (*str == 'h' || *str == 'l' || *str == j || *str == z ||
	*str == 't' || *str == 'L')
	{
		ft_strlcpy(opts->length, str, 2);
		return (1);
	}
	return (0);
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

const char *get_opt(const char *str, t_opt *opts) //%뒤의 문자열 주소값을 넣어줌.
{
	//유효성 검사 어떻게 할 지?
	int		i;

	i = 0;
	i += find_flag(str[i], opts);
	i += find_width(str + i, opts);
	if (str[i] == '.')
		i += find_prec(str[++i], opts);
	i += find_length(str + i, opts);
	i += find_type(str[i], opts);
	return (str + i);
}

int		ft_printf(const char *str, ...)
{
	va_list	ap;
	t_opt	opts;
	int		i;
	int		cnt;

	i = 0;
	cnt = 0;
	va_start(ap, str);//2번째 인자에 str넣는게 맞는지?
	while (str[i])
	{
		if (str[i] == '%')
		{
			//구조체에 각 옵션 값들 넣어줌.
			//가변인자 하나씩 받아서 *인 곳 바꿔주기
			if (opts->width == ??// = *일 떄 width에 넣어줄 값)
				opts->width = va_arg(ap, int); //음수일 경우도 고려해줘야함.
			//각 옵션의 조합 고려해서 출력
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