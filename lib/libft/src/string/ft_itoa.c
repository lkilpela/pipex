/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:09:11 by lkilpela          #+#    #+#             */
/*   Updated: 2023/11/15 13:17:33 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	intlen(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
	{
		len++;
		n = -n;
	}
	while (n > 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static void	convert_to_string_reverse(char *str, int n, int len)
{
	while (n > 0)
	{
		str[len] = (n % 10) + '0';
		n /= 10;
		--len;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		sign;

	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	if (n < 0)
		sign = -1;
	else
		sign = 1;
	len = intlen(n);
	str = (char *) malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	n *= sign;
	if (n == 0)
		str[0] = '0';
	else
	{
		convert_to_string_reverse(str, n, len - 1);
		if (sign == -1)
			str[0] = '-';
	}
	return (str);
}
