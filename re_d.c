//1. prec이 존재할 때
//  1. prec < buf_len일 때
//     무시하고 그냥 숫자 출력
//  2. prec >= buf_len일 때
//      기호 출력 후
//      buf_len - prec만큼 0 출력
//      숫자 출력
//  3. width - prec만큼 공백 출력(minus가 있으면 먼저 출력)
//2. prec이 없을 때
//  1. (숫자(+기호)) + (width - buf_len(-기호)만큼 공백(or 0) > 0) 출력(minus에 따라 순서 고려, zero에 따라 문자 고려)
//  2. 
// #include "ft_printf.h"

// char	*d_pre_task(va_list ap, t_opt *opts, int *n, int *size)
// {
// 	char	*buf;

// 	*n = va_arg(ap, int);
// 	if (opts->fg.hash || (opts->prec < 0  && *n == 0 && !opts->width))//경메 출력 조건
// 		return (0);
// 	if ((opts->fg.minus && opts->fg.zero) || opts->prec != 0)//0 flag 무시조건.
// 		opts->fg.zero = 0;
// 	if (opts->prec == -2)
// 		opts->fg.minus = 0;
// 	if (opts->prec >= opts->width)
// 	{
// 		*size = opts->prec;
// 		if (opts->fg.plus || opts->fg.space || n < 0)
// 			(*size)++;
// 	}
// 	else if (opts->width > opts->prec)
// 		*size = opts->width;
// 	buf = pf_itoa(*n);//pf_itoa는 기호 제외하고 숫자만 출력
// 	if (!buf)
// 		return (0);
// 	return (buf);
// }
// //공백, 부호, 숫자 or 부호 숫자 공백
// size_t	print_prec_buf(int n, t_opt opts, char *buf)
// {
// 	int		buf_len;
// 	size_t	cnt;

// 	cnt = 0;
// 	buf_len = (int)ft_strlen(buf);
// 	if (!opts.fg.zero)
// 		cnt += print_sign(opts, n);
// 	if (opts.prec > buf_len)
// 		cnt += print_char('0', opts.prec - buf_len);
// 	cnt += print_str(buf, buf_len);
// 	return (cnt);
// }

// size_t	d_print_case(int n, int size, t_opt opts, char *buf)//prec있는 경우 && prec > buf_len인 경우
// {
// 	size_t	cnt;
// 	int		buf_len;
// 	size_t	print_len;

// 	cnt = 0;
// 	printf("\nn : %d\n", n);
// 	printf("opts.prec : %d\n", opts.prec);
// 	printf("\n");
// 	if (opts.prec < 0  && n == 0 && !opts.width)
// 	{
// 		free(buf);
// 		buf = 0;
// 		printf("\nflag\n");
// 	}
// 	buf_len = (int)ft_strlen(buf);
// 	if (size > buf_len)
// 	{
// 		if (opts.fg.minus)
// 			cnt += print_prec_buf(n, opts, buf);
// 		if (opts.width > opts.prec)
// 		{
// 			if (opts.prec > buf_len)
// 				print_len = opts.width - opts.prec;
// 			else
// 				print_len = opts.width - buf_len;
// 			if (opts.fg.plus || opts.fg.space || n < 0)//부호 출력 시
// 				print_len--;
// 			if (!opts.fg.zero)
// 				print_char(' ', print_len);
// 			else
// 			{
// 				print_sign(opts, n);
// 				print_char('0', print_len);
// 			}
// 		}
// 		if (!opts.fg.minus)
// 			cnt += print_prec_buf(n, opts, buf);
// 	}
// 	else
// 	{
// 		cnt += print_sign(opts, n);
// 		cnt += print_str(buf, ft_strlen(buf));
// 	}
// 	return (cnt);
// }

// void	d_print(va_list ap, t_opt opts, size_t *cnt)
// {
// 	int		n;
// 	int		size;
// 	char	*buf;

// 	n = 0;
// 	size = 0;
// 	buf = d_pre_task(ap, &opts, &n, &size);
// 	if (buf == 0)
// 		return ;
// 	*cnt = d_print_case(n, size, opts, buf);
// }
