/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 09:25:19 by lkilpela          #+#    #+#             */
/*   Updated: 2024/03/07 15:17:48 by lkilpela         ###   ########.fr       */
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
		"Command not found",
		"No such file or directory"
	};

	return (error_messages[e]);
}

void	error(int e, t_pipex *p)
{
	const char	*message;
	int			i;

	if (e >= 0 || e < LAST_ERROR)
	{
		message = get_error_messages(e);
		write(2, "pipex: ", 7);
		i = 0;
		while (i < p->argc)
		{
			write(2, p->argv[i], ft_strlen(p->argv[i]));
			write(2, " ", 1);
			i++;
		}
		write(2, ": ", 2);	
		write(2, message, ft_strlen(message));
	}
	else
		write (2, "pipex: Unknown error", 21);
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}
