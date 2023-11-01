/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_typefinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 09:23:05 by luis-ffe          #+#    #+#             */
/*   Updated: 2023/10/12 12:24:34 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_typefinder(int type, va_list lst)
{
	if ('c' == type)
		return (ft_putchar_fd(va_arg(lst, int), 1));
	else if ('s' == type)
		return (ft_putstr_fd(va_arg(lst, char *), 1));
	else if ('p' == type)
		return (ft_putptr0x(va_arg(lst, unsigned long long), 1));
	else if ('d' == type || 'i' == type)
		return (ft_putnbr_fd(va_arg(lst, int), 1));
	else if ('u' == type)
		return (ft_putunsignd_fd(va_arg(lst, unsigned int), 1));
	else if ('x' == type)
		return (ft_puthex(va_arg(lst, unsigned int), 1, 1));
	else if ('X' == type)
		return (ft_puthex(va_arg(lst, unsigned int), 1, 42));
	else if ('%' == type)
		return (ft_putchar_fd(type, 1));
	return (0);
}
