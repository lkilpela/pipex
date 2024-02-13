/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:58:32 by lkilpela          #+#    #+#             */
/*   Updated: 2024/02/01 15:09:28 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_parse(const char *format, va_list ap)
{
	int	len;

	len = 0;
	if (*format == 'c')
		len = ft_putchar(va_arg(ap, int));
	else if (*format == 's')
		len = ft_putstr(va_arg(ap, char *));
	else if (*format == 'd' || *format == 'i')
		len = ft_putnbr(va_arg(ap, int));
	else if (*format == 'u')
		len = ft_putunbr(va_arg(ap, unsigned int));
	else if (*format == 'x')
		len = ft_puthex(va_arg(ap, unsigned int), 0);
	else if (*format == 'X')
		len = ft_puthex(va_arg(ap, unsigned int), 1);
	else if (*format == 'p')
		len = ft_putptr(va_arg(ap, void *));
	else if (*format == '%')
		len = ft_putchar('%');
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		len;
	int		temp;

	len = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			temp = ft_parse((++format), ap);
			if (temp == -1)
				return (-1);
			len += temp;
		}
		else
		{
			if (ft_putchar(*format) == -1)
				return (-1);
			len++;
		}
		format++;
	}
	va_end(ap);
	return (len);
}
