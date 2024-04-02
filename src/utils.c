/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:37:58 by lkilpela          #+#    #+#             */
/*   Updated: 2024/04/02 10:37:00 by lkilpela         ###   ########.fr       */
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

void	cleanup(t_pipex *p)
{
	int	i;

	i = 0;
	if (p->paths)
		free_paths(p->paths);
	while(i != 2)
	{
		if (p->cmds[1].args)
			free_paths(p->cmds[i].args);
		if (p->cmds[i].path)
			free(p->cmds[i].path);
		i++;
	}
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
