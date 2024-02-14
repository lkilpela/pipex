/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:08:08 by lkilpela          #+#    #+#             */
/*   Updated: 2024/02/14 22:27:06 by lkilpela         ###   ########.fr       */
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

// concatenates the directory, '/' & cmd to form a full path to the executable
char	*find_executable(t_pipex *p)
{
	int	i;

	i = 0;
	while (p->paths[i])
	{
		p->full_path = ft_strjoin(p->paths[i], p->slash_path);
		if (!p->full_path)
			return (NULL);
		printf("Allocated memory for p->full_path at %p\n", (void*)p->full_path);
		//free(p->slash_path);
		printf("Freed memory for p->slash_path\n");
		if (access(p->full_path, F_OK | X_OK) == 0)
		{
			//free_paths(p->paths);
			return (p->full_path);
		}
		free(p->full_path);
		printf("Freed memory for p->full_path at %p\n", (void*)p->full_path);
		i++;
	}
	//free_paths(p->paths);
	return (NULL);
}
//Find the environment path for Unix commands (e.g grep, ls, cat, etc.)
char **get_envpaths(t_pipex *p)
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

// determining the full path of a command
char	*find_command(t_pipex *p)
{
	int	i;

	i = 0;
	if (!p->cmd || !*p->cmd)
		return (NULL);
	else if (ft_strchr(*p->cmd, '/'))
		return (ft_strdup(*p->cmd));
	p->paths = get_envpaths(p);
	if (!p->paths)
		return (NULL);
	p->slash_path = ft_strjoin("/", *p->cmd);
	if (!p->slash_path)
		return (NULL);
	return (find_executable(p));
}
