/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_print1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 16:50:30 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/06/14 16:50:32 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		*f_pre_tesk(t_value *val, va_list ap, t_opt *opts)
{
	int	*bits;
	//가변인자를 공용체에 받기
	val->f = va_arg(ap, double);
	//flag 중복 처리
	if (opts->fg.plus && opts->fg.space)
		return (0);
	if (opts->fg.minus)//0 flag 무시조건.
		opts->fg.zero = 0;
	if (opts->prec == 0)//prec의 기본값 = 6
		opts->prec = 6;
	//이진데이터 처리
	if (!(bits = (int *)malloc(64 * sizeof(int))))
		return (0);
	ft_memset(bits, 0, sizeof(bits));
	trans_to_bin(bits, val->n);
	return (bits);
}

void	take_decimal(int *bits, t_real *num)//expo < 0인 경우
{
	int		expo;
	int		i;
	int		dec[52];//가수부 저장 배열
	double	tmp;

	ft_memset(dec, 0, sizeof(dec));
	expo = trans_to_dex(bits + 1, 11) - 1023;//1023은 bias상수
	//expo가 양수일 때와 음수일 때를 구분하여 이진 소수데이터를 dec에 저장
	i = -1;
	//가수부 비트만 따로 저장.
	if (expo == -1023)//지수부가 0인 경우 => 그대로 0.0으로 냅둠
		return ;
	if (expo >= 0)
		while (++i < 52 - expo)
			dec[i] = bits[12 + expo + i];
	else
	{
		expo *= -1;
		dec[expo - 1] = 1;
		while (++i < 52 - expo)
			dec[expo + i] = bits[12 + i];
	}
	num->deci = 0.0;
	i = 0;
	//가수부 비트 => 십진수로 계산
	while (i < 52)
	{
		tmp = (1.0 / (double)power(2, i + 1));
		if (dec[i++])
			num->deci += tmp;
	}
	num->deci += (double)num->integ;
}

double	round_deci(double num, int len)
{
	size_t	cpr;
	size_t	i_cpr;
	size_t	i_num;
	double	d_num;
	double	tmp;

	d_num = num * (double)power(10, len);
	i_num = (size_t)d_num;
	tmp = 0.5 - (0.1 / (double)power(10, 15 - len));
	cpr = (size_t)(tmp * power(10, 15 - len + 1));
	i_cpr = ((d_num - i_num) * (double)power(10, 15 - len + 1));
	if (i_cpr == cpr && i_num % 2 == 0)
		return (num);
	cpr = 5 * power(10, 15 - len);
	if (i_cpr == cpr && i_num % 2 == 0)
		return (num);
	d_num += 0.5 + (0.1 / (double)power(10, 15 - len));
	return (d_num / (double)(power(10, len)));
	/*
	1. 실수의 소수점 부분을 받음
	2. 소수점의 반올림 위치만큼 정수로 만들어줌.
	3. 만약 소수부가 15 - 반올림만큼 == 4 99999이거나 0.5인 경우 => 정수부가 짝수이면 버림
		else => 0.5 더해줌.
			=>4.99999구하는 방법
				1. 5.0에 0.1 / 10^(15 - len)만큼을 빼주고 10^(15 - len + 1)만큼 곱해줌 => 499999
				2. 5.0에 10^(15 - len + 1)만큼 곱해줌 => 5000000
				3. num의 반올림 다음 숫자가 위의 숫자들과 같은지 확인?
					=> 반올림 숫자까지 정수로 만들어 놓은 상태에서
					1. 정수부분 빼줌
					2. 10^(15 - len + 1)만큼 곱해줌
					3. 정수형에 저장

	*/
}

void	f_div_section(int *bits, t_value val, t_real *num, t_opt opts)
{
	int	tmp;

	tmp = 0;
	num->sign = 1;
	if (bits[0])
		num->sign = -1;
	num->integ = pf_absol_n((int)(val.f));
	/* 반올림
	만약 val.f의 소수부가 정확히 0.5인 경우(식별 방법은?)
		=> val.f의 정수부가 짝수면 버림, 홀수면 올림. 
	----소수부에서의 반올림-----
	반올림 할 구역의 값이 정확히 0.5인 경우
	*/
	//소수부분 처리
	take_decimal(bits, num);
	num->deci = round_deci(num->deci, opts.prec);
	num->integ = pf_absol_n((int)(num->deci));
	free(bits);
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
