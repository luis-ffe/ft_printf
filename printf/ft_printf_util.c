/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 20:06:11 by luis-ffe          #+#    #+#             */
/*   Updated: 2023/10/10 20:36:01 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putptr(unsigned long long num, int fd)
{
	int     x;

	if (num < 17)
	{
		return(write(fd, &"0123456789abcdef"[num], 1));
	}
	else
	{
		x = ft_putptr(num / 16, fd);
		ft_putptr(num % 16, fd);
	}
	return (x);
}

int	ft_putptr0x(unsigned long long num, int fd)
{
	int i;

	i = 0;
	if (num)
	{
		i += write(fd, "0", 1);
		i += write(fd, "x", 1);
	}
	return(i + ft_putptr(num, fd));
}

int	ft_putchar_fd(char c, int fd)
{
	return(write(fd, &c, 1));
}

int	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return (i);
	while (s[i])
		write (fd, &s[i++], 1);
	return (i - 1);
}

int	ft_putnbr_fd(int n, int fd)
{
	long    num;
	int     x;
	num = n;
	x = 0;
	if (num < 0)
	{
			num *= -1;
			x += write(fd, "-", 1);
	}
	if (num < 10)
	{
		num += '0';
		x += ft_putchar_fd(num, fd);
	}
	else
	{
		x += ft_putnbr_fd(num / 10, fd);
		ft_putnbr_fd(num % 10, fd);
	}
	return (x);
}

int	ft_puthex(unsigned int num, int fd, int j)
{
	int     x;

	if (num < 17)
	{
		if(j == 1)
			return(write(fd, &"0123456789abcdef"[num], 1));
		else
			return(write(fd, &"0123456789ABCDEF"[num], 1));
	}
	else
	{
		x = ft_puthex(num / 16, fd, j);
		ft_puthex(num % 16, fd, j);
	}
	return (x);
}

int	ft_typefinder(int type, va_list lst)
{
	int x;

	x = 0;
	if('c' == type)
		return (ft_putchar_fd(va_arg(lst, int), 1));
	else if('s' == type)
		return (ft_putstr_fd(va_arg(lst, char *), 1));
	else if('p' == type)
		return (ft_putptr0x(va_arg(lst, unsigned long long), 1));
	else if('d' == type)
		return (ft_putnbr_fd(va_arg(lst, int), 1));
	else if('i' == type)
		return (ft_putnbr_fd(va_arg(lst, int), 1)); 
	else if('u' == type)
		return (ft_putnbr_fd(va_arg(lst, unsigned int), 1));
	else if('x' == type)
		return (ft_puthex(va_arg(lst, unsigned int), 1, 1));
	else if('X' == type)
		return (ft_puthex(va_arg(lst, unsigned int), 1, 42));
	else if('%' == type) 
		return (ft_putchar_fd(type, 1));
	return (0);
}

int	ft_printf(const char *input, ...)
{
	int		i;
	va_list list;

	va_start(list, input);
	i = 0;
	while(*input)
	{
		if (*input == '%')
		{
			input++;
			i += ft_typefinder(*input, list);
		}
		else

			i += ft_putchar_fd(*input, 1);
		input++;
	}
	va_end(list);
	return (i);
}
