/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:08:08 by lkilpela          #+#    #+#             */
/*   Updated: 2024/02/13 14:47:44 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


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
