/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 08:49:35 by lkilpela          #+#    #+#             */
/*   Updated: 2024/02/15 11:16:05 by lkilpela         ###   ########.fr       */
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
