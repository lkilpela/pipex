/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 09:25:19 by lkilpela          #+#    #+#             */
/*   Updated: 2024/04/04 14:29:26 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static const char	*get_error_messages(int e)
{
	static const char	*error_messages[] = {
		"No error",
		"syntax: ./pipex infile cmd1 cmd2 outfile",
		"no such file or directory",
		"command not found",
		"is a directory",
		"permission denied",
		"fork failed",
		"pipe failed",
		"dup2 failed",
		"execve failed",
		"open failed",
		"close failed",
		"waitpid failed",
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
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		ft_putstr_fd(message, STDERR_FILENO);
	}
	else
		ft_putstr_fd ("pipex: Unknown error", STDERR_FILENO);
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

void	error_with_arg(int e, const char *str)
{
	const char	*message;

	if (e >= 0 || e < LAST_ERROR)
	{
		message = get_error_messages(e);
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		ft_putstr_fd(message, STDERR_FILENO);
		if(str) 
		{
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putstr_fd(str, STDERR_FILENO);
		}
	}
	else
		ft_putstr_fd ("pipex: Unknown error", STDERR_FILENO);
	write(2, "\n", 1);
}
