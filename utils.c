/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:37:58 by lkilpela          #+#    #+#             */
/*   Updated: 2024/02/29 09:21:02 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_pipex(int argc, char **argv, char **envp, t_pipex *p)
{
	p->argc = argc;
	p->argv = argv;
	p->envp = envp;
	p->pids = -1;
	p->infilefd = -1;
	p->outfilefd = -1;
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

const char	*get_error_messages(int e)
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

char	**resize_array(char **old_array, int old_count, int new_count)
{
	char	**new_array;
	int		i;

	i = 0;	
	new_array = malloc(sizeof(char *) * (new_count + 1));
	if (new_array == NULL)
		return (NULL);
	while(i < old_count)
	{
		new_array[i] = old_array[i];
		i++;
	}
	free(old_array);
	return (new_array);
}
