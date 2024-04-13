/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:41:17 by lkilpela          #+#    #+#             */
/*   Updated: 2024/04/13 11:44:20 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <signal.h>

static int	handle_signal(t_pipex *p)
{
	if (p->wstatus == SIGINT || p->wstatus == SIGQUIT)
		print_error(SIGQUIT, "SIGQUIT or SIGINT received");
	else if (p->wstatus == SIGPIPE)
		print_error(SIGPIPE, "SIGPIPE received");
	else if (p->wstatus == SIGCHLD)
		print_error(SIGCHLD, "SIGCHLD received");
	else if (p->wstatus == SIGSEGV)
		print_error(SIGSEGV, "SIGSEGV received");
	else if (p->wstatus == SIGBUS)
		print_error(SIGBUS, "SIGBUS received");
	else if (p->wstatus == SIGKILL)
		print_error(SIGKILL, "SIGKILL received");
	else if (p->wstatus == SIGABRT)
		print_error(SIGABRT, "SIGABRT received");
	else if (p->wstatus == SIGTERM)
		print_error(SIGTERM, "terminated");
	else	
		print_error(ERR_UNKNOWN, "Unknown signal received");
	return (ERR_SIG + WTERMSIG(p->wstatus));
}

static int	check_status(t_pipex *p)
{
	if (WIFSIGNALED(p->wstatus) != 0)
		return (handle_signal(p));
	else
		return (WEXITSTATUS(p->wstatus));		
}

int	execute_commands(t_pipex *p)
{
	pid_t	pid;
	int		i;
	int		exec_status;

	i = 0;
	exec_status = execute_first_command(p);
	if (exec_status != 0)
		return (exec_status);
	exec_status = execute_second_command(p);
	if (exec_status != 0)
		return (exec_status);
	while (i < 2)
	{
		if (kill(p->pids[i], SIGTERM) == -1) {
			perror("kill");
			return 1;
		}
		pid = waitpid(p->pids[i], &p->wstatus, 0);
		if (pid == -1)
			error(ERR_WAITPID);
			
		p->ecode = check_status(p);
		printf("check status returing %d\n", p->wstatus);
		printf("check status returing %d\n", p->ecode);
		if (p->ecode > 255)
			p->ecode = 255;
		i++;
	}
	return (0);
}
