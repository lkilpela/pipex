/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:37:58 by lkilpela          #+#    #+#             */
/*   Updated: 2024/02/29 09:43:05 by lkilpela         ###   ########.fr       */
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
	p->child_cmd = NULL;
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

char	**resize_array(char **old_array, int old_count, int new_count)
{
	char	**new_array;
	int		i;

	i = 0;
	new_array = malloc(sizeof(char *) * (new_count + 1));
	if (new_array == NULL)
		return (NULL);
	while (i < old_count)
	{
		new_array[i] = old_array[i];
		i++;
	}
	free(old_array);
	return (new_array);
}
