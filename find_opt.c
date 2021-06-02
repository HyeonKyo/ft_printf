/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_opt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 15:43:20 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/06/02 15:43:23 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		find_flag(const char *str, t_opt *opts, size_t *i)
{
	char	c;

	if (str[*i] == '-')
		opts->fg.minus = 1;
	else if (str[*i] == '+')
		opts->fg.plus = 1;
	else if (str[*i] == ' ')
		opts->fg.space = 1;
	else if (str[*i] == '0')
		opts->fg.zero = 1;
	else if (str[*i] == '\'')
		opts->fg.apos = 1;
	else if (str[*i] == '#')
		opts->fg.hash = 1;
	else
	{
		opts->fg.none = 1;//flag가 없는 경우.
		return (0);
	}
	if (opts->fg.minus && opts->fg.zero)//경메가 뜨는 flag조합.
		return (-1);
	return (1);
}

void	find_width(const char *str, t_opt *opts, size_t *i)
{
	if (str[*i] == '*')
	{
		opts->width = -1;
		(*i)++;
	}
	else
		opts->width = pf_atoi(str, opts, i);
}

void	find_prec(const char *str, t_opt *opts, size_t *i)
{
	if (str[*i] == '*')
	{
		opts->prec = -1;
		(*i)++;
	}
	else if (str[*i] == '-')
		opts->width = pf_atoi(str, opts, i);
	else if (ft_isdigit(str[*i]))
	{
		opts->prec = pf_atoi(str, opts, i);
		if (opts->prec == 0)
			opts->prec = -3; //.0인경우
	}
	else
		opts->prec = -2; //.만 있는 경우
}

void	find_length(const char *str, t_opt *opts, size_t *i)
{
	if (str[*i] == 'h' && str[*i + 1] == 'h')
		opts->ln.hh = 1;
	else if (str[*i] == 'l' && str[*i + 1] == 'l')
		opts->ln.ll = 1;
	else if (str[*i] == 'h')
		opts->ln.h = 1;
	else if (str[*i] == 'l')
		opts->ln.l = 1;
	else if (str[*i] == 'j')
		opts->ln.j = 1;
	else if (str[*i] == 'z')
		opts->ln.z = 1;
	else if (str[*i] == 't')
		opts->ln.t = 1;
	else if (str[*i] == 'L')
		opts->ln.L = 1;
	else
	{
		opts->ln.none = 1;
		return ;
	}
	if (opts->ln.hh || opts->ln.ll)
		*i += 2;
	else
		(*i)++;
}

int		find_type(char c, t_opt *opts)
{
	if (c == 'd' || c == 'i' || c == 'u' || c == 'o' || c == 'x'
	|| c == 'X' || c == 'f' || c == 'F' || c == 'e' || c == 'E'
	|| c == 'g' || c == 'G' || c == 'a' || c == 'A' || c == 'c'
	|| c == 's' || c == 'p' || c == 'n' || c == '%')
	{
		opts->type = c;
		return (1);
	}
	return (0);
}
