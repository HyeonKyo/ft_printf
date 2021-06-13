#include "ft_printf.h"

void	trans_to_bin(int *bits, size_t num)
{
	int	i;
	int	j;
	int	buf[64];

	i = 0;
	j = 0;
	while (num)
	{
		buf[i++] = num % 2;
		num /= 2;
	}
	buf[i++] = num % 2;
	while (i)
		bits[j++] = buf[--i];
}

size_t		power(int base, int e)
{
	size_t	n;

	n = 1;
	if (e == 0)
		return (1);
	if (base == 0)
		return (0);
	while (e)
	{
		n *= base;
		e--;	
	}
	return (n);
}

int		trans_to_dex(int *bits, int size)
{
	int	n;
	int	i;

	n = 0;
	i = 0;
	while (size)
		n += bits[--size] * power(2, i++);
	return (n);
}

static int	*f_pre_tesk(t_value *val, va_list ap, t_opt *opts)
{
	int	*bits;
	//가변인자를 공용체에 받기
	val->f = va_arg(ap, double);
	//flag 중복 처리
	if (opts->fg.plus && opts->fg.space)
		return (0);
	if (opts->fg.minus)//0 flag 무시조건.
		opts->fg.zero = 0;
	if (opts->prec >= 0 && opts->prec < 6)//prec의 기본값 = 6
		opts->prec = 6;
	//이진데이터 처리
	bits = (int *)malloc(64 * sizeof(int));
	ft_memset(bits, 0, sizeof(int *));
	trans_to_bin(bits, val->n);
	return (bits);
}

void	take_decimal(int *bits, t_real *num, t_opt opts)
{
	int		expo;
	int		idx;
	int		n;
	double	sum;
	double	tmp;

	expo = trans_to_dex(bits + 1, 11) - 1023;//1023은 bias상수
	idx = expo + 12;
	n = 1;
	sum = 0.0;
	tmp = 0.0;
	while (idx < 64)
	{
		tmp = 1 / (double)power(2, n++);
		if (bits[idx++])
			sum += tmp;
	}
	//여기서 prec으로 뒤에 붙는 0까지 처리하려 했으나
	//size_t범위를 넘어서는 오버플로우로 인해 에러 발생
	num->deci = (size_t)((sum * power(10, opts.prec)) + 0.5);
}

void	div_section(int *bits, t_value val, t_real *num, t_opt opts)
{
	int	i;

	i = 0;
	num->sign = 1;
	if (bits[0])
		num->sign = -1;
	if (opts.prec < 0)
		val.f += 0.5;
	num->integ= (int)val.f;
	//소수부분 처리
	take_decimal(bits, num, opts);
	free(bits);
}

size_t	print_space(t_opt opts, int len)
{
	size_t	cnt;

	cnt = 0;
	if (len > 0)
	{
		if (opts.fg.zero)
			cnt += print_char('0', len);
		else
			cnt += print_char(' ', len);
	}
	return (cnt);
}

size_t	f_print_all(t_real num, t_opt opts, char *i_buf, char *d_buf)
{
	size_t	cnt;

	cnt = 0;
	cnt += print_sign(opts, num.sign);
	cnt += print_str(i_buf, ft_strlen(i_buf));
	cnt += print_char('.', 1);
	cnt += print_str(d_buf, ft_strlen(d_buf));
	return (cnt);
}


size_t	f_print_case(t_real num, t_opt opts, char *i_buf, char *d_buf)
{
	int		len;
	size_t	cnt;

	cnt = 0;
	len = opts.width - (ft_strlen(i_buf) + ft_strlen(d_buf) + 1);
	if (opts.fg.plus || opts.fg.space || num.sign < 0)
		len--;
	if (opts.fg.minus)
	{
		cnt += f_print_all(num, opts, i_buf, d_buf);
		cnt += print_space(opts, len);
	}
	else
	{
		cnt += print_space(opts, len);
		cnt += f_print_all(num, opts, i_buf, d_buf);
	}
	return (cnt);
}

void	f_print(va_list ap, t_opt opts, size_t *cnt)
{
	t_value	val;
	t_real	num;
	int		*bits;
	char	*i_buf;
	char	*d_buf;

	ft_memset(&val, 0, sizeof(t_value));
	ft_memset(&num, 0, sizeof(t_real));
	bits = f_pre_tesk(&val, ap, &opts);
	div_section(bits, val, &num, opts);
	i_buf = pf_itoa((long long)num.integ);
	d_buf = pf_itoa((long long)num.deci);
	*cnt += f_print_case(num, opts, i_buf, d_buf);
	free(i_buf);
	free(d_buf);
}




/*
1. 공용체로 가변인자 값 받음.
	union / double과 size_t를 가지고 있음.
	1.5. flag등 사전 처리.
		=> 오류 상황
			1. + ' ' 동시에 쓰일 때
			2. - 0 동시에 쓰일 때
			3. prec = .0(or .)일 때 => 소수점 이하 출력 x, 반올림.(이거 자동으로 처리되게 작성)
			4. prec = .0(or .) , f = 0.0일 때 => 0만 출력(+, -, 0flag모두 정상 작동)
2. 정수형으로 저장된 데이터를 비트형태로 변환 가능.
	1. 정수를 2로 0이 될 때 까지 나눔
	2. 나머지 값을 계속 배열에 저장(1 or 0)
	3. 역순으로 나열하면 그게 비트로 표현한 데이터임.
3. 부호, 지수, 가수부분을 구분함.
	부호 : 맨 앞의 숫자가 1인지 0인지
	지수부 : 11자리 인트형 배열에 각 값 저장(1 or 0)
	가수부 : 52자리 인트형 배열에 각 값 저장
4. precision등의 값을 참고하여 십진수로 변환(반올림 적용)
    반올림 방법
	1. 가수부의 소수점 이하의 값을 십진수로 표현 => 어떻게?
		=>지수부 숫자 만큼 가수부앞의 자리부터 잘라냄
		=> 남은 가수부의 숫자들이 소수를 구성하는 숫자가 됨.
		=> 앞에서부터 2^-1, 2^-2, ...., 2^-n값을 나타냄
		=> 그 값들에 맞게 더해주면 소수 값이 나옴. 그 소수값을 변수 f라고 함.
		=> 만약 6자리 출력해야 한다면 f = f * 10^6을 하고,(자동으로 뒤에 0 붙음 => precision고려 x?)
			n = (size_t)f + 0.5를 하면 소수부분의 값을 정수 형태로 저장 가능함.
			그 정수형태의 숫자를 출력하면 됨.(itoa?)
5. 십진수 출력
*/

/*
함수 1. 사전 처리 함수(가변인자 받음, flag 중복, 에러 처리)
함수 2. 실수 저장 값의 비트에 맞게 부호, 지수, 가수부를 나눔.
	=> 함수 2-1 : 2진수로 계속 나눠서 10진수 정수를 int형 배열[64]에 0 or 1(2진수)로 저장.
	=> 함수 2-2 : 부호, 정수, 소수 부분 나눠 저장.
		=> 부호는 맨 앞이 0인지 1인지 확인(1 = 음수)
		=> 정수 부분은 실수를 정수형으로 캐스팅하면 됨.(. .0인 경우는 0.5를 더하고 캐스팅)
		=> 소수부분
			=> 지수부 숫자만큼 가수부 앞에서부터 버림(함수 2-3 : 2진수를 다시 10진수로 변경)
			=> 남은 가수부의 앞에서 부터 n번째가 1이면 + (2^-(n + 1))을 의미함.(거듭제곱함수 필요.)
				따라서 그 값들을 다 실수형 변수에 더해줌.(반복문 idx를 n으로 활용, 길면 함수로 뺌.)
			=> 출력해야하는 소수점 아래의 길이만큼 10^n만큼 곱해주고, 0.5를 더하면서 정수로 캐스팅
			=> 출력할 만큼의 숫자를 정수로 저장. => 나중에 소수 출력 시 이 숫자를 그대로 출력
3. case에 맞는 출력
	부호, 정수, 소수 부분을 flag, width에 맞춰서 출력 (prec은 함수2의 소수부분에서 해결하도록.)
*/