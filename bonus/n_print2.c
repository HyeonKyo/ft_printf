/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_print2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 14:38:40 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/06/20 14:38:41 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	n_print(va_list ap, t_opt opts, size_t *cnt)
{
	if (opts.ln.hh)
		arg_hhn(ap, *cnt);
	if (opts.ln.h)
		arg_hn(ap, *cnt);
	if (opts.ln.l)
		arg_ln(ap, *cnt);
	if (opts.ln.ll)
		arg_lln(ap, *cnt);
	arg_n(ap, *cnt);
}
