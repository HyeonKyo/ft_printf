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
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <wchar.h>
# include "../libft/libft.h"

typedef struct	s_flag
{
	int	minus;
	int	plus;
	int	space;
	int	zero;
	int	apos;
	int	hash;
}				t_flag;

typedef struct	s_length
{
	int	hh;
	int	h;
	int	l;
	int	ll;
}				t_length;

typedef struct	s_opt
{
	t_flag		fg;
	int			width;
	int			prec;
	t_length	ln;
	char		type;
}				t_opt;

/*
** 실수를 공용체로 저장함.
*/
typedef union	u_value
{
	size_t	n;
	double	f;
}				t_value;

/*
** 실수의 각 부분의 정보를 따로 저장(부호, 정수, 소수부)
*/
typedef struct	s_real
{
	int		sign;
	int		integ;
	double	deci;
	int		point;
}				t_real;

typedef unsigned long long	t_ull;

/*
** utils1
*/
int				print_char(char c, int len);
int				pf_absol_n(int n);
int				pf_atoi(const char *str, size_t *i);
char			*pf_itoa(long long n);
/*
** utils2
*/
char			*pf_uitoa(unsigned long long n);
int				print_sign(t_opt opts, long long n);
size_t			print_str(char *str, size_t len);
int				check_sign(t_opt opts, long long n);
/*
** utils3
*/
void			trans_to_bin(int *bits, size_t num);
size_t			power(int base, int e);
int				trans_to_dex(int *bits, int size);
/*
** find_opt
*/
int				find_flag(const char *str, t_opt *opts, size_t *i);
void			find_width(const char *str, t_opt *opts, size_t *i);
void			find_prec(const char *str, t_opt *opts, size_t *i);
void			find_length(const char *str, t_opt *opts, size_t *i);
int				find_type(char c, t_opt *opts);
/*
** get_opt
*/
int				get_opt(const char *str, t_opt *opts, size_t *i);
/*
** c_print
*/
size_t			c1_print(int c);
size_t			c2_print(int n);
size_t			c3_print(int n);
size_t			c4_print(int n);
int				c_case_cnt(int c, t_opt opts);
size_t			c_case_print(int c, t_opt opts);
void			c_print(va_list ap, t_opt opts, size_t *cnt);
/*
** d_print
*/
void			d_print(va_list ap, t_opt opts, size_t *cnt);
char			*d_pre_task(va_list ap, t_opt *opts, long long *n);
/*
** u_print
*/
t_ull			get_arg_u(va_list ap, t_opt *opts);
char			*u_pre_task(va_list ap, t_opt *opts, t_ull *n);
size_t			u_print_all(t_opt opts, char *buf);
void			u_print(va_list ap, t_opt opts, size_t *cnt);
/*
** x_print
*/
int				get_size_based(unsigned long long n, int base);
char			*pf_itoa_hex(unsigned long long n, t_opt opts);
char			*x_pre_task(va_list ap, t_opt *opts, unsigned long long *n);
void			x_print(va_list ap, t_opt opts, size_t *cnt);
/*
** s_print
*/
int				get_print_len(va_list ap, t_opt opts);
void			s_print(va_list ap, t_opt opts, size_t *cnt);
/*
** p_print
*/
void			p_print(va_list ap, t_opt opts, size_t *cnt);
/*
** f_print1
*/
int				*f_pre_tesk(t_value *val, va_list ap, t_opt *opts);
void			take_decimal(int *bits, t_real *num);
void			f_div_section(int *bits, t_value val, t_real *num, t_opt opts);
/*
** f_print2
*/
size_t			print_space(t_opt opts, t_real num, int len);
size_t			print_deci(t_real num, int len);
void			f_print(va_list ap, t_opt opts, size_t *cnt);
/*
** e_print
*/
void			e_print(va_list ap, t_opt opts, size_t *cnt);
/*
** n_print
*/
void			arg_hhn(va_list ap, size_t cnt);
void			arg_hn(va_list ap, size_t cnt);
void			arg_ln(va_list ap, size_t cnt);
void			arg_lln(va_list ap, size_t cnt);
void			arg_n(va_list ap, size_t cnt);
void			n_print(va_list ap, t_opt opts, size_t *cnt);
/*
** ft_print.c
*/
int				ft_printf(const char *str, ...);
#endif
