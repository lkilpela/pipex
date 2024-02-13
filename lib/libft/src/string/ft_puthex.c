/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:14:17 by lkilpela          #+#    #+#             */
/*   Updated: 2024/01/30 14:14:29 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puthex(unsigned long num, int is_upper)
{
	char	*hex;
	int		len;

	if (is_upper)
		hex = "0123456789ABCDEF";
	else
		hex = "0123456789abcdef";
	if (num >= 16)
	{
		len = ft_puthex(num / 16, is_upper);
		if (len == -1)
			return (-1);
	}
	else
		len = 0;
	if (write(1, &hex[num % 16], 1) == -1)
		return (-1);
	return (len + 1);
}
