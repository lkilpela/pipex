/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:08:08 by lkilpela          #+#    #+#             */
/*   Updated: 2024/02/13 13:05:33 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// "PATH=/usr/local/bin:/usr/bin:/bin"
char *find_path(t_pipex *p)
{
	int	i;

	i = 0;
	while (p->envp[i] && !ft_strncmp(p->envp[i], "PATH=", 5))
		i++;
	if (!p->envp[i] || ft_strlen(p->envp[i]) < 5)
	{
		ft_printf("PATH environment variable not found\n");
		return (NULL);
	}
	p->paths = ft_split(p->envp[i] + 5, ':');
	if (!p->paths)
	{
		ft_printf("Failed to split PATH\n");
		return (NULL);
	}
	return (p->paths[0]);
}
