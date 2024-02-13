/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 12:07:32 by lkilpela          #+#    #+#             */
/*   Updated: 2024/02/12 11:35:12 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*merge_string(char *s1, char *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	if(!s1 && s2) {
		return ft_strdup(s2);
	}

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = (char *) malloc(len1 + len2 + 1);
	if (result)
	{
		ft_memcpy(result, s1, len1);
		ft_memcpy(result + len1, s2, len2);
		result[len1 + len2] = '\0';
	}
	free(s1);
	return (result);
}

static char	*read_until_newline(int fd, char *buffer)
{
	int		read_count;
	char	read_buf[BUFFER_SIZE + 1];

	read_count = read(fd, read_buf, BUFFER_SIZE);
	while (read_count > 0)
	{
		read_buf[read_count] = '\0';
		buffer = merge_string(buffer, read_buf);
		if (!buffer || ft_strchr(read_buf, '\n'))
			break ;
		read_count = read(fd, read_buf, BUFFER_SIZE);
	}
	if (read_count < 0 || !buffer)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

static char	*extract_line(char **buffer)
{
	char	*line;
	char	*copy;
	char	*pos;

	line = *buffer;
	pos = ft_strchr(line, '\n');
	if (pos)
	{
		*buffer = ft_strdup(pos + 1);
		pos[1] = '\0';
	}
	else
	{
		line = *buffer;
		*buffer = NULL;
	}
	//if (!*line)
	//{
	//	free(line);
	//	return (NULL);
	//}
	copy = ft_strdup(line);
	free(line);
	return (copy);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	//if (!buffer)
	//	buffer = ft_strdup("");
	buffer = read_until_newline(fd, buffer);
	if (!buffer)
		return (NULL);
	line = extract_line(&buffer);
	if (!line && buffer)
	{
		free(buffer);
		buffer = NULL;
	}
	return (line);
}
