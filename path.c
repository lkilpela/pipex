/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:08:08 by lkilpela          #+#    #+#             */
/*   Updated: 2024/02/15 10:47:28 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//Find the environment path for Unix commands (e.g grep, ls, cat, etc.)
char	**get_envpaths(t_pipex *p)
{
	int	i;

	i = 0;
	while (p->envp[i] && ft_strncmp(p->envp[i], "PATH=", 5) != 0)
		i++;
	if (!p->envp[i] || ft_strlen(p->envp[i]) < 5)
		return (NULL);
	return (ft_split(p->envp[i] + 5, ':'));
}

// concatenates the directory, '/' & cmd to form a full path to the executable
char	*find_executable(t_pipex *p)
{
	int	i;

	i = 0;
	while (p->paths[i])
	{
		p->full_path = ft_strjoin(p->paths[i], p->slash_cmd);
		if (!p->full_path)
			return (NULL);
		if (access(p->full_path, F_OK | X_OK) == 0)
			return (p->full_path);
		free(p->full_path);
		i++;
	}
	return (NULL);
}

// determining the full path of a command
char	*find_command(t_pipex *p)
{
	int		i;
	char	*command;

	i = 0;
	if (!p->cmd || !*p->cmd)
		return (NULL);
	else if (ft_strchr(*p->cmd, '/'))
		return (ft_strdup(*p->cmd));
	p->paths = get_envpaths(p);
	if (!p->paths)
		return (NULL);
	p->slash_cmd = ft_strjoin("/", *p->cmd); //"/ls" or "/grep"
	if (!p->slash_cmd)
	{
		free_paths(p->paths);
		return (NULL);
	}
	p->full_path = find_executable(p);
	if (!p->full_path)
	{
		free(p->slash_cmd);
		free_paths(p->paths);
	}
	return (p->full_path);
}
