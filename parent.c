/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:41:17 by lkilpela          #+#    #+#             */
/*   Updated: 2024/03/01 09:07:26 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int handle_signal(int status)
{
	int	signal_number;

	if (signal_number == WTERMSIG(status))
}

int wait_children(t_pipex *p, t_tokenize *t, char *cmd)
{
	pid_t	pid;
	int		i;
	int		status;
	int		exit_status;

	i = 0;
	exit_status = 0;
	status = execute_first_command(p, t, cmd);
	if (status != 0)
		return (status);
	status = execute_second_command(p, t, cmd);
	if (status != 0)
		return (status);
	while (i < 2)
	{
		pid = waitpid(p->pid[i], &status, 0);
		if (pid == -1)
			error(ERR_WAITPID);
		else if (WIFEXITED(status)) 
			exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			
		}
		i++;
	}
	return (exit_status);
}
