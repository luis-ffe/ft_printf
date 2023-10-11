/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 07:31:18 by luis-ffe          #+#    #+#             */
/*   Updated: 2023/10/06 15:59:34 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
