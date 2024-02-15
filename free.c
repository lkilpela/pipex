/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 08:49:35 by lkilpela          #+#    #+#             */
/*   Updated: 2024/02/15 10:09:56 by lkilpela         ###   ########.fr       */
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

char    *cleanup(t_pipex *p)
{
	if (p->paths)
	{
		free_paths(p->paths);
		p->paths = NULL;
	}
	if (slash->path)
	{
		free(p->paths);
		p->paths = NULL;
	}
    return (NULL);
}