/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:12:39 by lkilpela          #+#    #+#             */
/*   Updated: 2024/01/30 14:12:50 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(int n)
{
	char	c;
	int		len;

	if (n == -2147483648)
		return (ft_putstr("-2147483648"));
	if (n < 0)
	{
		len = ft_putchar('-');
		if (len == -1)
			return (-1);
		n *= -1;
	}
	else
		len = 0;
	if (n >= 10)
	{
		len += ft_putnbr(n / 10);
		if (len == -1)
			return (-1);
	}
	c = n % 10 + '0';
	if (write(1, &c, 1) == -1)
		return (-1);
	return (len + 1);
}
