/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:13:19 by lkilpela          #+#    #+#             */
/*   Updated: 2024/01/30 14:13:29 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putunbr(unsigned int n)
{
	char	c;
	int		len;

	if (n >= 10)
	{
		len = ft_putunbr(n / 10);
		if (len == -1)
			return (-1);
	}
	else
		len = 0;
	c = n % 10 + '0';
	if (write(1, &c, 1) == -1)
		return (-1);
	return (len + 1);
}
