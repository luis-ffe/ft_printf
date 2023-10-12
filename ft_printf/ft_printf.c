/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 08:38:33 by luis-ffe          #+#    #+#             */
/*   Updated: 2023/10/12 07:32:13 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

int	ft_num_len(unsigned	int num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num = num / 10;
	}
	return (len);
}

static long int	countnbr(int c)
{
	int	size;

	size = 0;
	if (c <= 0)
		size = 1;
	while (c)
	{
		c = c / 10;
		size++;
	}
	return (size);
}

static char	*set_nbr_str(unsigned int aux, char *s, long int size)
{
	while (aux > 0)
	{
		s[size--] = (aux % 10) + '0';
		aux = aux / 10;
	}
	return (s);
}

char	*ft_itoa(int n)
{
	char			*s;
	long int		size;
	unsigned int	aux;

	size = countnbr(n);
	s = (char *)malloc(sizeof(char) * (size + 1));
	if (!s)
		return (NULL);
	s[size--] = '\0';
	if (n == 0)
		s[0] = '0';
	if (n < 0)
	{
		aux = n * -1;
		s[0] = '-';
	}
	else
		aux = n;
	s = set_nbr_str(aux, s, size);
	return (s);
}

int	ft_putptr(unsigned long long num, int fd)
{
	int     x;
	unsigned long long l;

	x = 0;
	l = num;
	if (num == 0)
		return(write(fd, "0", 1));
	if (num < 16)
	{
		return(write(fd, &"0123456789abcdef"[num], 1));
	}
	else
	{
		x += ft_putptr(num / 16, fd);
		x += ft_putptr(num % 16, fd);
	}
	return (x);
}

int	ft_putptr0x(unsigned long long num, int fd)
{
	int i;

	i = 0;
	if (!num)
		return(write(fd, "(nil)", 5));
	else
	{
		write(fd, "0", 1);
		write(fd, "x", 1);
	}
	return((num == 0) ? ((ft_putptr(num, fd) + 2) || (ft_putptr(num, fd) + 1)));
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
		return (write (1, "(null)", 6));
	while (s[i])
		write (fd, &s[i++], 1);
	return (i);
}

int	ft_putnbr_fd(int n, int fd)
{
	char	*s;
	
	s = ft_itoa(n);
	return (ft_putstr_fd(s, fd));
}

char	*ft_uitoa(unsigned int n)
{
	char	*num;
	int		len;

	len = ft_num_len(n);
	num = (char *)malloc(sizeof(char) * (len + 1));
	if (!num)
		return (0);
	num[len] = '\0';
	while (n != 0)
	{
		num[len - 1] = n % 10 + 48;
		n = n / 10;
		len--;
	}
	return (num);
}

int	ft_putunsignd_fd(unsigned int n, int fd)
{
	char	*s;
	
	s = ft_uitoa(n);
	return (ft_putstr_fd(s, fd));
}

int	ft_puthex(unsigned int num, int fd, int j)
{
	int     x;
	unsigned int n;

	x = 0;
	n = num;
	if (num < 16)
	{
		if(j == 1)
			write(fd, &"0123456789abcdef"[num], 1);
		else
			write(fd, &"0123456789ABCDEF"[num], 1);
	}
	else
	{
		ft_puthex(num / 16, fd, j);
		ft_puthex(num % 16, fd, j);
	}
	while(n)
	{
		n /= 16;
		x++;
	}
	return (x);
}

int	ft_typefinder(int type, va_list lst)
{
	if('c' == type)
		return (ft_putchar_fd(va_arg(lst, int), 1));
	else if('s' == type)
		return (ft_putstr_fd(va_arg(lst, char *), 1));
	else if('p' == type)
		return (ft_putptr0x(va_arg(lst, unsigned long long), 1));
	else if('d' == type || 'i' == type)
		return (ft_putnbr_fd(va_arg(lst, int), 1));
	else if('u' == type)
		return (ft_putunsignd_fd(va_arg(lst, unsigned int), 1));
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
			if (*input != '%' && *input)
			{
				i += ft_typefinder(*input, list);
			}
			else
				i += ft_putchar_fd(*input, 1);
		}
		else
			i += ft_putchar_fd(*input, 1);
		input++;
	}
	va_end(list);
	return (i);
}

int main(void)
{
	int output_OG;
	int output_FT;

/////////////////////////////////
//  	  NO SPECIFIERS		   //
/////////////////////////////////
	ft_printf("----------------NO SPECIFIERS---------------\n");
	output_OG = printf("OG -> Test String \t TEeeEEEeEEsT String\n");
	output_FT = ft_printf("FT -> Test String \t TEeeEEEeEEsT String\n");
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	output_OG = printf("OG -> T \t t \n");
	output_FT = ft_printf("FT -> T \t t \n");
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

/////////////////////////////////
//				%c			   //
/////////////////////////////////
	ft_printf("------------%%c------------\n");
	char	ltr = 'C';
	output_OG = printf("OG -> I love %c\n", ltr);
	output_FT = ft_printf("FT -> I love %c\n", ltr);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	ltr = '\0';
	output_OG = printf("OG -> %c\n", ltr);
	output_FT = ft_printf("FT -> %c\n", ltr);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	output_OG = printf("OG -> %c\n", '0' + 256);
	output_FT = ft_printf("FT -> %c\n", '0' + 256);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	output_OG = printf("OG -> %c %c %c \n", '1', '2', '3');
	output_FT = ft_printf("FT -> %c %c %c \n", '1', '2', '3');
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	output_OG = printf("OG -> %c %c %c \n", '2', '1', 0);
	output_FT = ft_printf("FT -> %c %c %c \n", '2', '1', 0);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	output_OG = printf("OG -> %c %c %c \n", ' ', ' ', ' ');
	output_FT = ft_printf("FT -> %c %c %c \n", ' ', ' ', ' ');
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	output_OG = printf("OG -> %c %c %c \n", '0', 0, '1');
	output_FT = ft_printf("FT -> %c %c %c \n", '0', 0, '1');
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");
	
/////////////////////////////////
//				%s			   //
/////////////////////////////////
	ft_printf("------------%%s------------\n");
	char	*str = "Nuno";
	output_OG = printf("OG -> Hi I'm %s\n", str);
	output_FT = ft_printf("FT -> Hi I'm %s\n", str);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	char	long_str[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab";
	output_OG = printf("OG -> %s\n", long_str);
	output_FT = ft_printf("FT -> %s\n", long_str);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	char str2[] = "Atirei o pau no gatis, per gatis num morreus.";
	output_OG = printf("OG -> %s\n", str2);
	output_FT = ft_printf("FT -> %s\n", str2);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	output_OG = printf("OG -> %s\n", "");
	output_FT = ft_printf("FT -> %s\n", "");
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	output_OG = printf("OG -> %s\n", "-");
	output_FT = ft_printf("FT -> %s\n", "-");
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	output_OG = printf("OG -> %s %s\n", "-", "4");
	output_FT = ft_printf("FT -> %s %s\n", "-", "4");
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	output_OG = printf("OG -> %s %s%s\n", "-", "4", "2");
	output_FT = ft_printf("FT -> %s %s%s\n", "-", "4", "2");
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	char	*dummy = NULL;
	output_OG = printf("OG -> This should be NULL: %s\n", dummy);
	output_FT = ft_printf("FT -> This should be NULL: %s\n", dummy);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

/////////////////////////////////
//				%p			   //
/////////////////////////////////
	ft_printf("------------%%p------------\n");
	char	*ptr = "c";
	output_OG = printf("OG -> %p\n", ptr);
	output_FT = ft_printf("FT -> %p\n", ptr);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");
	
	void *dummy_ptr = NULL;
	output_OG = printf("OG -> %p\n", dummy_ptr);
	output_FT = ft_printf("FT -> %p\n", dummy_ptr);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	output_OG = printf("OG -> %p\n", (void *)-2);
	output_FT = ft_printf("FT -> %p\n", (void *)-2);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");
	
	output_OG = printf("OG -> %p\n", (void *)-1);
	output_FT = ft_printf("FT -> %p\n", (void *)-1);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");
	
	output_OG = printf("OG -> %p\n", (void *)1);
	output_FT = ft_printf("FT -> %p\n", (void *)1);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	output_OG = printf("OG -> %p\n", (void *)15);
	output_FT = ft_printf("FT -> %p\n", (void *)15);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	output_OG = printf("OG -> %p\n", (void *)16);
	output_FT = ft_printf("FT -> %p\n", (void *)16);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	output_OG = printf("OG -> %p\n", (void *)17);
	output_FT = ft_printf("FT -> %p\n", (void *)17);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	ft_printf("LONG_MIN && LONG_MAX------------------------\n");

	output_OG = printf("OG ->  %p %p \n", (void*)LONG_MIN, (void*)LONG_MAX);
	output_FT = ft_printf("FT ->  %p %p \n", (void*)LONG_MIN, (void*)LONG_MAX);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	ft_printf("INT_MIN && INT_MAX------------------\n");
	output_OG = printf("OG ->  %p %p \n", (void*)INT_MIN, (void*)INT_MAX);
	output_FT = ft_printf("FT ->  %p %p \n", (void*)INT_MIN, (void*)INT_MAX);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	ft_printf("ULONG_MAX && -ULONG_MAX------\n");
	output_OG = printf("OG ->  %p %p \n", (void*)ULONG_MAX, (void*)-ULONG_MAX);
	output_FT = ft_printf("FT ->  %p %p \n", (void*)ULONG_MAX, (void*)-ULONG_MAX);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	ft_printf("0 && 0--------------------\n");
	output_OG = printf("OG ->  %p %p \n", (void*)0, (void*)0);
	output_FT = ft_printf("FT ->  %p %p \n", (void*)0, (void*)0);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);






/////////////////////////////////
//				%d			   //
/////////////////////////////////
	ft_printf("------------%%d------------\n");
	ft_printf("POSITIVE NUMBERS----------\n");
	int		nbr_pos = 42;
	output_OG = printf("OG -> %d\n", nbr_pos);
	output_FT = ft_printf("FT -> %d\n", nbr_pos);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");
	
	ft_printf("INT_MAX-------------------\n");
	output_OG = printf("OG -> %d\n", INT_MAX);
	output_FT = ft_printf("FT -> %d\n", INT_MAX);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	ft_printf("NEGATIVE NUMBERS----------\n");
	int		nbr_neg = -42;
	output_OG = printf("OG -> %d\n", nbr_neg);
	output_FT = ft_printf("FT -> %d\n", nbr_neg);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	nbr_neg = -1000000;
	output_OG = printf("OG -> %d\n", nbr_neg);
	output_FT = ft_printf("FT -> %d\n", nbr_neg);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	output_OG = printf("OG -> very long negative number: %d\n", -50000454);
	output_FT = ft_printf("FT -> very long negative number: %d\n", -50000454);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");
	
	ft_printf("INT_MIN--------------------\n");
	output_OG = printf("OG -> %d\n", INT_MIN);
	output_FT = ft_printf("FT -> %d\n", INT_MIN);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

/////////////////////////////////
//				%i			   //
/////////////////////////////////
	ft_printf("------------%%i------------\n");
	int		nbr_i = 42;
	output_OG = printf("OG -> %i\n", nbr_i);
	output_FT = ft_printf("FT -> %i\n", nbr_i);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

/////////////////////////////////
//				%u			   //
/////////////////////////////////
	ft_printf("------------%%u------------\n");
	unsigned nbr_u = 42;
	output_OG = printf("OG -> %u\n", nbr_u);
	output_FT = ft_printf("FT -> %u\n", nbr_u);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	output_OG = printf("OG -> %u\n", 4294967295u);
	output_FT = ft_printf("FT -> %u\n", 4294967295u);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	nbr_u = -16;
	output_OG = printf("OG -> %u\n", nbr_u);
	output_FT = ft_printf("FT -> %u\n", nbr_u);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	nbr_u = -101;
	output_OG = printf("OG -> %u\n", nbr_u);
	output_FT = ft_printf("FT -> %u\n", nbr_u);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	nbr_u = INT_MAX;
	output_OG = printf("OG -> %u\n", nbr_u);
	output_FT = ft_printf("FT -> %u\n", nbr_u);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	nbr_u = INT_MIN;
	output_OG = printf("OG -> %u\n", nbr_u);
	output_FT = ft_printf("FT -> %u\n", nbr_u);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	nbr_u = -9;
	output_OG = printf("OG -> %u\n", nbr_u);
	output_FT = ft_printf("FT -> %u\n", nbr_u);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	nbr_u = -99;
	output_OG = printf("OG -> %u\n", nbr_u);
	output_FT = ft_printf("FT -> %u\n", nbr_u);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	nbr_u = -10;
	output_OG = printf("OG -> %u\n", nbr_u);
	output_FT = ft_printf("FT -> %u\n", nbr_u);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

/////////////////////////////////
//				%x			   //
/////////////////////////////////
	ft_printf("------------%%x------------\n");
	unsigned nbr_x = 520;
	output_OG = printf("OG -> %x\n", nbr_x);
	output_FT = ft_printf("FT -> %x\n", nbr_x);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	output_OG = printf("OG -> 17 in hexadecimal = %x\n", 17);
	output_FT = ft_printf("FT -> 17 in hexadecimal = %x\n", 17);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	output_OG = printf("OG -> 999999 in hexadecimal = %x\n", 999999);
	output_FT = ft_printf("FT -> 999999 in hexadecimal = %x\n", 999999);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	output_OG = printf("OG -> 4294967293 in hexadecimal = %x\n", 4294967293u);
	output_FT = ft_printf("FT -> 4294967293 in hexadecimal = %x\n", 4294967293u);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");


	output_OG = printf("OG -> %d\n", -100);
	output_FT = ft_printf("FT -> %d\n", -100);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	output_OG = printf("OG -> %d\n", -15);
	output_FT = ft_printf("FT -> %d\n", -15);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");
	
	output_OG = printf("OG -> %x\n", 10);
	output_FT = ft_printf("FT -> %x\n", 10);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	output_OG = printf("OG -> %x\n", 11);
	output_FT = ft_printf("FT -> %x\n", 11);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	output_OG = printf("OG -> %x\n", -42);
	output_FT = ft_printf("FT -> %x\n", -42);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	output_OG = printf("OG -> %x\n", 42);
	output_FT = ft_printf("FT -> %x\n", 42);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	output_OG = printf("OG -> %x\n", 15);
	output_FT = ft_printf("FT -> %x\n", 15);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	output_OG = printf("OG -> %x\n", 1000);
	output_FT = ft_printf("FT -> %x\n", 1000);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");
	
	output_OG = printf("OG -> %x\n", 0);
	output_FT = ft_printf("FT -> %x\n", 0);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	output_OG = printf("OG -> %x\n", 1);
	output_FT = ft_printf("FT -> %x\n", 1);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	output_OG = printf("OG -> %x\n", 9);
	output_FT = ft_printf("FT -> %x\n", 9);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");
	
	output_OG = printf("OG -> %x\n", -1);
	output_FT = ft_printf("FT -> %x\n", -1);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	output_OG = printf("OG -> %x\n", -2);
	output_FT = ft_printf("FT -> %x\n", -2);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");
	
	output_OG = printf("OG -> %x\n", -101);
	output_FT = ft_printf("FT -> %x\n", -101);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	output_OG = printf("OG -> %x\n", INT_MAX);
	output_FT = ft_printf("FT -> %x\n", INT_MAX);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	output_OG = printf("OG -> %x\n", INT_MIN);
	output_FT = ft_printf("FT -> %x\n", INT_MIN);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	output_OG = printf("OG -> %x\n", UINT_MAX);
	output_FT = ft_printf("FT -> %x\n", UINT_MAX);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	output_OG = printf("OG -> %x\n", 100);
	output_FT = ft_printf("FT -> %x\n", 100);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	output_OG = printf("OG -> %x\n", -99);
	output_FT = ft_printf("FT -> %x\n", -99);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	output_OG = printf("OG -> %x\n", -16);
	output_FT = ft_printf("FT -> %x\n", -16);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");
	
	output_OG = printf("OG -> %x\n", -9);
	output_FT = ft_printf("FT -> %x\n", -9);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	output_OG = printf("OG -> %x\n", -14);
	output_FT = ft_printf("FT -> %x\n", -14);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	output_OG = printf("OG -> %x\n", 16);
	output_FT = ft_printf("FT -> %x\n", 16);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	output_OG = printf("OG -> %x\n", 99);
	output_FT = ft_printf("FT -> %x\n", 99);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	output_OG = printf("OG -> %x\n", 101);
	output_FT = ft_printf("FT -> %x\n", 101);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	output_OG = printf("OG -> %x\n", -11);
	output_FT = ft_printf("FT -> %x\n", -11);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	output_OG = printf("OG -> %x\n", -10);
	output_FT = ft_printf("FT -> %x\n", -10);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	output_OG = printf("OG -> %x\n", 17);
	output_FT = ft_printf("FT -> %x\n", 17);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

/////////////////////////////////
//				%X			   //
/////////////////////////////////
	ft_printf("------------%%X------------\n");
	unsigned nbr_X = 520;
	output_OG = printf("OG -> %X\n", nbr_X);
	output_FT = ft_printf("FT -> %X\n", nbr_X);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

/////////////////////////////////
//		% PERCENTAGE TESTS	   //
/////////////////////////////////
	ft_printf("------------%%%%------------\n");
	output_OG = printf("OG -> %%\n");
	output_FT = ft_printf("FT -> %%\n");
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");
	
	output_OG = printf("OG -> %% %%\n");
	output_FT = ft_printf("FT -> %% %%\n");
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	output_OG = printf("OG -> %% %% %%\n");
	output_FT = ft_printf("FT -> %% %% %%\n");
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");

	output_OG = printf("OG -> %%  %%  %%\n");
	output_FT = ft_printf("FT -> %%  %%  %%\n");
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("--------------------------------MIX-------------------------------\n");
	output_OG = printf("OG -> %%%s %%%s %%%d %clbum \t 520 in hexadecimal is %x\n", "string1", "string2", 18, 'a', 520);
	output_FT = ft_printf("FT -> %%%s %%%s %%%d %clbum \t 520 in hexadecimal is %x\n", "string1", "string2", 18, 'a', 520);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	ft_printf("\n");


		ft_printf("\n");

	nbr_neg = -99999999;
	output_OG = printf("OG -> %d\n", nbr_neg);
	output_FT = ft_printf("FT -> %d\n", nbr_neg);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

		nbr_neg = 99999999;
	output_OG = printf("OG -> %d\n", nbr_neg);
	output_FT = ft_printf("FT -> %d\n", nbr_neg);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

		nbr_neg = -9999;
	output_OG = printf("OG -> %d\n", nbr_neg);
	output_FT = ft_printf("FT -> %d\n", nbr_neg);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

		nbr_neg = 9999;
	output_OG = printf("OG -> %d\n", nbr_neg);
	output_FT = ft_printf("FT -> %d\n", nbr_neg);
	printf("OUTPUT OG = %d\n", output_OG);
	ft_printf("OUTPUT FT = %d\n", output_FT);

	return (0);
}
