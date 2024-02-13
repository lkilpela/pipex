/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 08:55:00 by lkilpela          #+#    #+#             */
/*   Updated: 2023/11/24 12:18:17 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_word_count(const char *s, char c)
{
	int	count;
	int	in_substring;

	count = 0;
	in_substring = 0;
	while (*s != '\0')
	{
		if (*s == c)
			in_substring = 0;
		else if (*s != c && in_substring == 0)
		{
			in_substring = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static void	free_t(char **t)
{
	int		i;

	i = 0;
	while (t[i] != 0)
	{
		free(t[i]);
		i++;
	}
	free(t);
}

static char	**split_into_words(char const *s, char **t, char c, int word_count)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (j < word_count)
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			start = i;
			while (s[i] != c && s[i] != '\0')
				i++;
			t[j] = ft_substr(s, start, i - start);
			if (t[j] == NULL)
				return (NULL);
			j++;
		}
	}
	t[j] = NULL;
	return (t);
}

char	**ft_split(char const *s, char c)
{
	char	**t;
	int		word_count;
	char	**res;

	if (s == NULL)
		return (NULL);
	word_count = get_word_count(s, c);
	t = (char **)malloc((word_count + 1) * sizeof(char *));
	if (t == NULL)
		return (NULL);
	res = split_into_words(s, t, c, word_count);
	if (res == NULL)
		free_t(t);
	return (res);
}
