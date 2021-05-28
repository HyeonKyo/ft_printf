#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	t_opt	opts;
	int		i;
	int		cnt;

	i = 0;
	cnt = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			//while (type까지)
				//구조체에 option값들 넣어줌
			//가변인자를 받고 구조체의 플래그 조합으로
			//조건에 맞는 데이터 출력
			//cnt++
		}
		else
		{
			write(1, str + i, 1);
			cnt++;
		}
		i++;
	}
	return (cnt);
}