/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:41:17 by lkilpela          #+#    #+#             */
/*   Updated: 2024/02/29 15:12:53 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int parent_process(t_pipex *p, t_tokenize *t, char *cmd)
{
	int	status;
	int	exit_status;

	status = execute_first_command(p, t, cmd);
	if (status != 0)
		return (status);
	status = execute_second_command(p, t, cmd);
	if (status != 0)
		return (status);
	if (t->pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status)) 
		{
			exit_status = WEXITSTATUS(status);
		}
	}
	return (0);
}