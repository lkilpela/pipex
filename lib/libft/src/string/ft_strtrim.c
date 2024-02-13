/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 22:34:37 by lkilpela          #+#    #+#             */
/*   Updated: 2023/11/13 13:21:36 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	char	*result;

	if (s1 == NULL || set == NULL)
		return (NULL);
	while (*s1 != 0 && ft_strchr(set, *s1))
		s1++;
	len = ft_strlen(s1);
	while (len != 0 && ft_strchr(set, s1[len - 1]))
		len--;
	result = (char *) malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, s1, len + 1);
	return (result);
}
