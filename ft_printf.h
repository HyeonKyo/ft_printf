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

//utils1
int		print_char(char c, int len);
int		pf_atoi(const char *str, t_opt *opts, size_t *i);
int		get_size_based(long long n, int base);
size_t	absol_n(int n);
char	*pf_itoa(long long n);
//utils2
int		print_sign(t_opt opts, int n);
size_t	print_str(char *str, size_t len);
//find_opt
int		find_flag(const char *str, t_opt *opts, size_t *i);
void	find_width(const char *str, t_opt *opts, size_t *i);
void	find_prec(const char *str, t_opt *opts, size_t *i);
void	find_length(const char *str, t_opt *opts, size_t *i);
int		find_type(char c, t_opt *opts);
//get_opt
int		get_opt(const char *str, t_opt *opts, size_t *i);
//d_print
char	*d_pre_task(va_list ap, t_opt *opts, int *n, int *size);
size_t	print_sign_buf(int n, char *buf, t_opt opts);
size_t	d_print_case1(int n, int size, t_opt opts, char *buf);
size_t	d_print_case2(int n, int size, t_opt opts, char *buf);
void	d_print(va_list ap, t_opt opts, size_t *cnt);
//u_print
char	*u_pre_task(va_list ap, t_opt *opts, unsigned int *n, int *size);
size_t	u_print_case(int size, t_opt opts, char *buf);
void	u_print(va_list ap, t_opt opts, size_t *cnt);
//x_print
char	*pf_itoa_hex(unsigned long long n, t_opt opts);
char	*x_pre_task(va_list ap, t_opt *opts, unsigned int *n, int *size);
void	x_print(va_list ap, t_opt opts, size_t *cnt);
//s_print
void	s_print(va_list ap, t_opt opts, size_t *cnt);
//p_print
char	*p_pre_task(va_list ap, t_opt *opts, unsigned long long *n, int *size);
size_t	print_hex_addr(char *buf);
size_t	p_print_case(int print_size, t_opt opts, char *buf);
void	p_print(va_list ap, t_opt opts, size_t *cnt);
//print
void	c_print(va_list ap, t_opt opts, size_t *cnt);
void	print_arg(va_list ap, t_opt opts, size_t *cnt);
int		ft_printf(const char *str, ...);
#endif
