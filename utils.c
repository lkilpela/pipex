/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:37:58 by lkilpela          #+#    #+#             */
/*   Updated: 2024/02/15 11:24:27 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

static void	cleanup(t_pipex *p)
{
	if (p->full_path)
		free(p->full_path);
	if (p->slash_cmd)
		free(p->slash_cmd);
	if (p->paths)
		free_paths(p->paths);
	// Add more cleanup code as needed...
}

void	error(t_pipex *p, int e)
{
	const char *error_messages[] = {
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
		"write failed"
	};
	cleanup(p);
	if (e < 0 || e >= sizeof(error_messages) / sizeof(error_messages[0]))
		e = 0;  // Default to "No error" if e is out of range
	perror(error_messages[e]);
	exit(EXIT_FAILURE);
}
