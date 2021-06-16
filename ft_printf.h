/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 15:43:34 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/06/02 15:43:35 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
#include <stdio.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <wctype.h>
# include "./libft/libft.h"

typedef struct	s_flag
{
	int	none;
	int	minus;
	int	plus;
	int	space;
	int	zero;
	int	apos;
	int	hash;
}				t_flag;

typedef struct	s_length
{
	int	none;
	int	hh;
	int	h;
	int	l;
	int	ll;
	int	j;
	int	z;
	int	t;
	int L;
}				t_length;

typedef struct	s_opt
{
	t_flag		fg;
	int			width;
	int			prec;
	t_length	ln;
	char		type;
}				t_opt;

typedef union	u_value
{
	size_t		n;
	double 		f;
}				t_value;
//실수를 공용체로 저장함.

typedef struct	s_bi
{
	long long	high;
    long long	mid;
	long long	low;
}				t_bi;

typedef struct	s_real
{
	int		sign;
	int		integ;
	t_bi	deci;
	int		point;//e_print시 사용.
}				t_real;
//실수의 각 부분의 정보를 따로 저장(부호, 정수, 소수부)


//utils1
int		print_char(char c, int len);
int		pf_get_size(long long n);
int		pf_atoi(const char *str, t_opt *opts, size_t *i);
char	*pf_itoa(long long n);
//utils2
int		print_sign(t_opt opts, int n);
size_t	print_str(char *str, size_t len);
int		check_sign(t_opt opts, int n);
//utils3
void	trans_to_bin(int *bits, size_t num);
size_t		power(int base, int e);
int		trans_to_dex(int *bits, int size);
//find_opt
int		find_flag(const char *str, t_opt *opts, size_t *i);
void	find_width(const char *str, t_opt *opts, size_t *i);
void	find_prec(const char *str, t_opt *opts, size_t *i);
void	find_length(const char *str, t_opt *opts, size_t *i);
int		find_type(char c, t_opt *opts);
//get_opt
int		get_opt(const char *str, t_opt *opts, size_t *i);
//c_print
void	c_print(va_list ap, t_opt opts, size_t *cnt);
//d_print
void	d_print(va_list ap, t_opt opts, size_t *cnt);
//u_print
size_t	u_print_all(t_opt opts, char *buf);
void	u_print(va_list ap, t_opt opts, size_t *cnt);
//x_print
int		get_size_based(unsigned long long n, int base);
char	*pf_itoa_hex(unsigned long long n, t_opt opts);
void	x_print(va_list ap, t_opt opts, size_t *cnt);
//s_print
void	s_print(va_list ap, t_opt opts, size_t *cnt);
//p_print
void	p_print(va_list ap, t_opt opts, size_t *cnt);
//f_print1
int		*f_pre_tesk(t_value *val, va_list ap, t_opt *opts);
void	take_deci(int *bits, t_real *num);
void	f_div_section(int *bits, t_value val, t_real *num, t_opt opts);
//f_print2
size_t	print_space(t_opt opts, t_real num, int len);
size_t	print_deci(t_real num, int len);
void	f_print(va_list ap, t_opt opts, size_t *cnt);
//e_print
void	e_print(va_list ap, t_opt opts, size_t *cnt);

//ft_print.c
int		ft_printf(const char *str, ...);
#endif
