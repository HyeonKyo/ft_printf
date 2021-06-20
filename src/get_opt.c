/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 15:43:39 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/06/02 15:43:40 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	get_opt(const char *str, t_opt *opts, size_t *i)
{
	while (find_flag(str, opts, i) > 0)
		(*i)++;
	find_width(str, opts, i);
	if (str[*i] == '.')
	{
		(*i)++;
		find_prec(str, opts, i);
	}
	find_length(str, opts, i);
	if (!find_type(str[*i], opts))
		return (0);
	return (1);
}
/*
** 함수 인자 i는 %다음 인덱스 값
** flag는 반복문으로 받아줌
** 서식지정자 (type)이 없는 경우 0리턴(에러)
*/
