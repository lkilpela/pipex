/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:37:58 by lkilpela          #+#    #+#             */
/*   Updated: 2024/02/15 11:17:51 by lkilpela         ###   ########.fr       */
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

void cleanup(t_pipex *p)
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
	cleanup(p);
	if (e == ERR_SYNTAX)
		perror("Syntax: ./pipex infile cmd1 cmd2 outfile\n");
	else if (e == ERR_FORK)
		perror("fork failed\n");
	else if (e == ERR_PIPE)
		perror("pipe failed\n");
	else if (e == ERR_DUP2)
		perror("dup2 failed\n");
	else if (e == ERR_EXECVE)
		perror("execve failed\n");
	else if (e == ERR_MALLOC)
		perror("malloc failed\n");
	else if (e == ERR_OPEN)
		perror("open failed\n");
	else if (e == ERR_CLOSE)
		perror("close failed\n");
	else if (e == ERR_READ)
		perror("read failed\n");
	else if (e == ERR_WRITE)
		perror("write failed\n");
	else if (e == ERR_MEM)
		perror("Memory allocation failed\n");
	else
		perror("Unknown error\n");
	exit(EXIT_FAILURE);
}
