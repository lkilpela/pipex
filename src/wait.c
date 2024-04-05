/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:41:17 by lkilpela          #+#    #+#             */
/*   Updated: 2024/04/05 12:37:03 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_status(pid_t pid, int status)
{
	if (WEXITSTATUS(status) != 0)
		ft_printf("Child with PID %u exited with status %u.\n",
			(unsigned int)pid, WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		ft_printf("Child with PID %u was terminated by signal %u\n",
			(unsigned int)pid, WTERMSIG(status));
}

int	execute_commands(t_pipex *p)
{
	pid_t	pid;
	int		i;
	int		exec_status;
	int		wait_status;

	i = 0;
	exec_status = execute_first_command(p);
	if (exec_status != 0)
		return (exec_status);
	exec_status = execute_second_command(p);
	if (exec_status != 0)
		return (exec_status);
	while (i < 2)
	{
		pid = waitpid(p->pids[i], &wait_status, 0);
		if (pid == -1)
			error(ERR_WAITPID);
		child_status(pid, wait_status);
		i++;
	}
	return (0);
}
