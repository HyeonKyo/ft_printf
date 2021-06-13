/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 15:43:48 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/06/02 15:43:49 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_sign(t_opt opts, int n)
{
	if (opts.fg.plus && n > 0)
		write(1, "+", 1);
	else if (opts.fg.space && n > 0)
		write(1, " ", 1);
	else if (n < 0)
		write(1, "-", 1);
	else
		return (0);
	return (1);
}

size_t	print_str(char *str, size_t len)
{
	if (str[0] == 0 && len == 0)
	 	return (0);
	write(1, str, len);
	return (len);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (str == 0)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	*ft_memset(void *ptr, int value, size_t num)
{
	char	*str;
	size_t	i;

	i = 0;
	str = ptr;
	while (i < num)
		str[i++] = value;
	return (ptr);
}