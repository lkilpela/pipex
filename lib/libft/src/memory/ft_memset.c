/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:19:48 by lkilpela          #+#    #+#             */
/*   Updated: 2023/11/13 13:19:44 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*b_char;

	i = 0;
	b_char = (unsigned char *)b;
	while (i < len)
	{
		b_char[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
