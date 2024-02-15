/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 11:46:13 by lkilpela          #+#    #+#             */
/*   Updated: 2024/02/15 15:21:19 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// grep Hello | awk "'{count++} END {print count}'" 



char **tokenize(const char *arg)
{
	int i;
	int	len;
	
	i = 0;
	if(p->cmd_args == NULL)
		return (NULL);
	cmd = ft_split()
	p->cmd_args = malloc(MAX_TOKENS * sizeof(char *));
	if (!p->cmd_args)
		return (NULL);
}