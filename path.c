/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:08:08 by lkilpela          #+#    #+#             */
/*   Updated: 2024/02/13 15:39:25 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_paths(char **paths)
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

//Find the environment path for Unix commands (e.g grep, ls, cat, etc.)
char **find_path(t_pipex *p)
{
	int	i;

	i = 0;
	while (p->envp[i] && ft_strncmp(p->envp[i], "PATH=", 5) != 0)
		i++;
	if (!p->envp[i] || ft_strlen(p->envp[i]) < 5)
	{
		ft_printf("PATH environment variable not found\n");
		return (NULL);
	}
	return(ft_split(p->envp[i] + 5, ':'));
}

char *executable_path(t_pipex *p)
{
	int		i;
	char 	*slash_path;
	char	*full_path;
	
	i = 0;
	if (!p->cmd || !(*p->cmd))
		return (NULL);	
	p->paths = find_path(p);
	if (!p->paths)
		return (NULL);
	while (p->paths[i])
	{
		slash_path = ft_strjoin(p->paths[i], "/");
		full_path = ft_strjoin(slash_path, p->cmd);
		free(slash_path);
		if (access(full_path, F_OK) == 0)
		{
			free_paths(p->paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_paths(p->paths);
	return (NULL);
}
