/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 21:34:50 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/03/15 21:35:07 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	len_number(int n)
{
	int		len;
	long	nbr;

	nbr = n;
	if (n == 0)
	{
		return (1);
	}
	len = 0;
	if (nbr < 0)
	{
		len++;
		nbr = nbr * (-1);
	}
	while (nbr > 0)
	{
		nbr = nbr / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	nbr;
	int		length;
	char	*str;

	nbr = n;
	length = len_number(nbr);
	str = (char *)malloc((length + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (nbr == 0)
		str[0] = '0';
	if (nbr < 0)
	{
		str[0] = '-';
		nbr = nbr * (-1);
	}
	str[length--] = '\0';
	while (nbr != 0)
	{
		str[length--] = (nbr % 10) + '0';
		nbr = nbr / 10;
	}
	return (str);
}
