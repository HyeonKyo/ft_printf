#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdlib.h>

typedef struct	s_opt
{
	char	flag;
	int		width;
	int		prec;
	char	length[3];
	char	type;
}				t_opt;
