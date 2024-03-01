/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:41:17 by lkilpela          #+#    #+#             */
/*   Updated: 2024/03/01 09:33:46 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	wait_children(t_pipex *p, t_tokenize *t, char *cmd)
{
	pid_t	pid;
	int		i;
	int		status;

	i = 0;
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
			ft_printf("Child with PID %d exited with status %d.\n", pid,
				WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			ft_printf("Child with PID %d was terminated by signal %d.\n", pid,
				WTERMSIG(status));
		i++;
	}
	return (0);
}
