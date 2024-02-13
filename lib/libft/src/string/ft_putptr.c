/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:15:07 by lkilpela          #+#    #+#             */
/*   Updated: 2024/01/30 14:15:21 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putptr(void *p)
{
	int	len;
	int	hex_len;

	len = 0;
	len += write(1, "0x", 2);
	if (len == -1)
		return (-1);
	if (p == NULL)
	{
		if (write(1, "0", 1) == -1)
			return (-1);
		len += 1;
	}
	else
	{
		hex_len = ft_puthex((unsigned long)p, 0);
		if (hex_len == -1)
			return (-1);
		len += hex_len;
	}
	return (len);
}
