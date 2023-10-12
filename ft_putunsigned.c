/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 09:25:05 by luis-ffe          #+#    #+#             */
/*   Updated: 2023/10/12 12:28:40 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_uitoa(unsigned int n)
{
	char	*num;
	int		len;

	len = ft_num_len(n);
	num = (char *)malloc(sizeof(char) * (len + 1));
	if (!num)
	{
		free(num);
		return (0);
	}
	if (n == 0)
		num[0] = '0';
	num[len] = '\0';
	while (n)
	{
		num[--len] = n % 10 + 48;
		n = n / 10;
	}
	return (num);
}

int	ft_putunsignd_fd(unsigned int n, int fd)
{
	char	*s;
	int		x;

	x = 0;
	s = ft_uitoa(n);
	x = ft_putstr_fd(s, fd);
	free(s);
	return (x);
}
