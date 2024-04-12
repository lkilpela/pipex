/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:41:17 by lkilpela          #+#    #+#             */
/*   Updated: 2024/04/12 21:24:38 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*static void	check_status(pid_t pid, int status)
{
	if (WIFEXITED(status))
		ft_printf("Child with PID %u exited with status %u.\n",
			(unsigned int)pid, WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		ft_printf("Child with PID %u was terminated by signal %u\n",
			(unsigned int)pid, WTERMSIG(status));
	else
		ft_printf("Unexpected status %d\n", status);
}*/
static int	signal(int status)
{
	int	signal;

	if (WIFSIGNALED(status))
	{
		signal = WTERMSIG(status);
		if (signal == SIGINT || signal == SIGQUIT)
			print_error(SIGQUIT, "SIGQUIT or SIGINT received");
		else if (signal == SIGPIPE)
			print_error(SIGPIPE, "SIGPIPE received");
		else if (signal == SIGCHLD)
			print_error(SIGCHLD, "SIGCHLD received");
		else if (signal == SIGSEGV)
			print_error(SIGSEGV, "SIGSEGV received");
		else if (signal == SIGBUS)
			print_error(SIGBUS, "SIGBUS received");
		else if (signal == SIGKILL)
			print_error(SIGKILL, "SIGKILL received");
		else if (signal == SIGABRT)
			print_error(SIGABRT, "SIGABRT received");
		else if (signal == SIGTERM)
			print_error(SIGTERM, "SIGTERM received");
		return (ERR_SIG + signal);
	}
}

static void	check_status(pid_t pid, int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (signal_exit(status));
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
		check_status(pid, wait_status);
		i++;
	}
	return (0);
}
