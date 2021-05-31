#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdlib.h>

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
