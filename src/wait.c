/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:41:17 by lkilpela          #+#    #+#             */
/*   Updated: 2024/04/13 13:08:12 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <signal.h>

static char *join_arguments(t_pipex *p)
{
	static char	combined_args[1024] = "";
	int 		i;
	int 		pos = 0;

	i = 0;
	while (i < p->argc)
	{
		ft_strlcat(combined_args+pos, p->argv[i], 1024-pos);
		pos += strlen(p->argv[i]);
		if (i < p->argc - 1) {
            ft_strlcat(combined_args+pos, " ", 1024-pos);  // Add a space between arguments
            pos++;
        }
		i++;
	}
	return (combined_args);
}

static int	handle_signal(t_pipex *p)
{
	if (p->wstatus == SIGINT || p->wstatus == SIGQUIT)
		print_error(ERR_SIGQUIT, join_arguments(p));
	else if (p->wstatus == SIGPIPE)
		print_error(ERR_SIGPIPE, join_arguments(p));
	else if (p->wstatus == SIGCHLD)
		print_error(ERR_SIGCHLD, join_arguments(p));
	else if (p->wstatus == SIGSEGV)
		print_error(ERR_SIGSEGV, join_arguments(p));
	else if (p->wstatus == SIGBUS)
		print_error(ERR_SIGBUS, join_arguments(p));
	else if (p->wstatus == SIGKILL)
		print_error(ERR_SIGKILL, join_arguments(p));
	else if (p->wstatus == SIGABRT)
		print_error(ERR_SIGABRT, join_arguments(p));
	else if (p->wstatus == SIGTERM)
		print_error(ERR_SIGTERM, join_arguments(p));
	else	
		print_error(ERR_SIGOTHR, join_arguments(p));
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
		join_arguments(p);
		if (kill(p->pids[i], SIGBUS) == -1) {
			perror("kill");
			return 1;
		}
		pid = waitpid(p->pids[i], &p->wstatus, 0);
		if (pid == -1)
			error(ERR_WAITPID);		
		p->ecode = check_status(p);
		ft_printf("Child %d exited with status %d\n", pid, p->ecode);
		if (p->ecode > 255)
			p->ecode = 255;
		i++;
	}
	return (0);
}
