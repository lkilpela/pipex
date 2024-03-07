/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 09:25:19 by lkilpela          #+#    #+#             */
/*   Updated: 2024/03/07 08:31:25 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static const char	*get_error_messages(int e)
{
	static const char	*error_messages[] = {
		"No error",
		"Syntax: ./pipex infile cmd1 cmd2 outfile",
		"Memory allocation failed",
		"fork failed",
		"pipe failed",
		"dup2 failed",
		"execve failed",
		"malloc failed",
		"open failed",
		"close failed",
		"read failed",
		"write failed",
		"waitpid failed",
		"Command is not valid",
		"Filename is not valid",
		"Command not found"
	};

	return (error_messages[e]);
}

void	error(int e)
{
	char	*message;

	if (e >= 0 || e < LAST_ERROR)
	{
		message = get_error_messages(e);
		write(1, message, ft_strlen(message));
	}	
	else
		write (1, "Unknown error\n", 14);
	exit(EXIT_FAILURE);
}
