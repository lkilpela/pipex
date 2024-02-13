/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:08:08 by lkilpela          #+#    #+#             */
/*   Updated: 2024/02/13 12:55:09 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char *find_path(t_pipex *p)
{
	int	i;

	i = 0;
	while (p->envp[i] && !ft_strncmp(p->envp[i], "PATH=", 5))
		i++;
    
}