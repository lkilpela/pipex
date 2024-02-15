/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:37:58 by lkilpela          #+#    #+#             */
/*   Updated: 2024/02/15 20:51:40 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init(int argc, char **argv, char **envp, t_pipex *p)
{
	p->argc = argc;
	p->argv = argv;
	p->envp = envp;
	p->pids = -1;
	p->infile = -1;
	p->outfile = -1;
	p->paths = NULL;
	p->child_path = NULL;
	p->parent_path = NULL;
	p->child_cmd= NULL;
	p->parent_cmd = NULL;
}

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
	if (p->child_path)
		free(p->child_path);
	if (p->parent_path)
		free(p->parent_path);
	if (p->paths)
		free_paths(p->paths);
}

void	error(t_pipex *p, int e)
{
	const char	*error_messages[] = {
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
		e = 0;
	perror(error_messages[e]);
	exit(EXIT_FAILURE);
}
