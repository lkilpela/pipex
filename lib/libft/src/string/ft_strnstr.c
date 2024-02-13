/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:32:56 by lkilpela          #+#    #+#             */
/*   Updated: 2023/11/13 15:19:13 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	n;

	n = ft_strlen(needle);
	if (*needle == 0)
		return ((char *)haystack);
	while (*haystack != 0 && n <= len)
	{
		if (ft_strncmp(haystack, needle, n) == 0)
			return ((char *)haystack);
		++haystack;
		--len;
	}
	return (0);
}
