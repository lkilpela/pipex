/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 11:46:13 by lkilpela          #+#    #+#             */
/*   Updated: 2024/02/15 15:00:38 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// grep Hello | awk "'{count++} END {print count}'" 

char **tokenize(t_pipex *p, char *cmd)
{
	int i;
	
	i = 0;
	if(p->cmd_args == NULL)
		return (NULL);	
}