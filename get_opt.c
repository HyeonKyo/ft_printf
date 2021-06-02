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

int	get_opt(const char *str, t_opt *opts, size_t *i)//%뒤의 문자열 주소값을 넣어줌.
{
	int	ret;
	//유효성 검사 어떻게 할 지?
	while ((ret = find_flag(str, opts, i)) > 0)
		(*i)++;
	if (ret == -1)
		return (0); //flag가 -와 0이 있는 경우의 에러상황(기존 함수는 경고메시지 출력 후 0옵션 무시)
	find_width(str, opts, i);
	if (str[*i] == '.')
	{
		(*i)++;
		find_prec(str, opts, i);
	}
	find_length(str, opts, i);
	if (!find_type(str[*i], opts))
		return (0);//서식지정자가 없는 에러상황
	return (1);
}
