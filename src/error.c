/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 09:25:19 by lkilpela          #+#    #+#             */
/*   Updated: 2024/03/07 22:30:42 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static const char	*get_error_messages(int e)
{
	static const char	*error_messages[] = {
		"No error",
		"Syntax: ./pipex infile cmd1 cmd2 outfile",
		"fork failed",
		"pipe failed",
		"dup2 failed",
		"execve failed",
		"open failed",
		"close failed",
		"waitpid failed",
		"Command is not valid",
		"Filename is not valid",
		"Permission denied",
		"No such file or directory",
		"Permission denied",
		"Permission denied",
		"Is directory",
		"Command not found",
		"last error"
	};

	return (error_messages[e]);
}

void	error(int e)
{
	const char	*message;

	if (e >= 0 || e < LAST_ERROR)
	{
		message = get_error_messages(e);
		write(2, "pipex: ", 7);
		write(2, message, ft_strlen(message));
	}
	else
		write (2, "pipex: Unknown error", 21);
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}
