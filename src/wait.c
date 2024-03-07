/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:41:17 by lkilpela          #+#    #+#             */
/*   Updated: 2024/03/07 15:31:01 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_status(pid_t pid, int status)
{
	if (WIFEXITED(status))
		ft_printf("Child with PID %u exited with status %u.\n",
			(unsigned int)pid, WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		ft_printf("Child with PID %u was terminated by signal %u\n",
				(unsigned int)pid, WTERMSIG(status));
}

int	wait_children(t_pipex *p, t_tokenize *t)
{
	pid_t	pid;
	int		i;
	int		status;

	i = 0;
	status = execute_first_command(p, t);
	if (status != 0)
		return (status);
	status = execute_second_command(p, t);
	if (status != 0)
		return (status);
	while (i < 2)
	{
		pid = waitpid(p->pids[i], &status, 0);
		if (pid == -1)
			error(ERR_WAITPID, &p);
		else
			child_status(pid, status);
		i++;
	}
	return (0);
}
