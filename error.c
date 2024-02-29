/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 09:25:19 by lkilpela          #+#    #+#             */
/*   Updated: 2024/02/29 10:20:31 by lkilpela         ###   ########.fr       */
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
		"Command not found"
	};

	return (error_messages[e]);
}

void	error(int e)
{
	if (e >= 0 || e < LAST_ERROR)
		perror(get_error_messages(e));
	else
		perror ("Unknown error");
	exit(EXIT_FAILURE);
}
