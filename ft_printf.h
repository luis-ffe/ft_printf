/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 20:07:26 by luis-ffe          #+#    #+#             */
/*   Updated: 2023/10/12 12:25:59 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

int		ft_putstr_fd(char *s, int fd);
int		ft_putnbr_fd(int n, int fd);
int		ft_num_len(unsigned	int num);
int		ft_putptr0x(unsigned long long num, int fd);
int		ft_putptr(unsigned long long num, int fd);
char	*set_nbr_str(unsigned int aux, char *s, long int size);
int		countnbr(int c);
char	*ft_itoa(int n);
int		ft_putchar_fd(char c, int fd);
char	*ft_uitoa(unsigned int n);
int		ft_putunsignd_fd(unsigned int n, int fd);
int		ft_typefinder(int type, va_list lst);
int		ft_printf(const char *input, ...);
int		ft_puthex(unsigned int num, int fd, int j);

#endif