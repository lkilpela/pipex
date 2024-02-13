/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:52:50 by lkilpela          #+#    #+#             */
/*   Updated: 2023/11/16 11:08:20 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*last_occurrence;

	last_occurrence = NULL;
	while (*s != '\0')
	{
		if (*s == (char)c)
		{
			last_occurrence = (char *)s;
		}
		++s;
	}
	if ((char)c == '\0')
		last_occurrence = (char *)s;
	return ((char *)last_occurrence);
}
