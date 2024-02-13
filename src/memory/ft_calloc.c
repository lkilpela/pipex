/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:36:57 by lkilpela          #+#    #+#             */
/*   Updated: 2023/11/14 11:18:22 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (size != 0 && count > SIZE_MAX / size)
	{
		return (NULL);
	}
	ptr = (void *) malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	if (ptr != 0)
	{
		ft_bzero(ptr, count * size);
	}
	return (ptr);
}
