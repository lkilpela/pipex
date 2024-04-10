/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:49:47 by lkilpela          #+#    #+#             */
/*   Updated: 2024/04/10 12:05:20 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	setup_pipe(t_pipex *p)
{
	if (pipe(p->pipefd) == -1)
		error(ERR_PIPE);
}

//system("leaks pipex");
int	main(int argc, char **argv, char **envp)
{
	t_pipex	p;
	int		status;
	char    lsof_cmd[256];

	init_pipex(argc, argv, envp, &p);
	validate_arguments(&p);
	setup_pipe(&p);
	
	// Add a 1-second delay
    sleep(1);

    // Run lsof to check open files
    sprintf(lsof_cmd, "lsof -p %d", getpid());
    system(lsof_cmd);
	
	status = execute_commands(&p);
	if (status != 0)
	{
		cleanup(&p);
		return (status);
	}

	// Add a 1-second delay
    sleep(1);

    // Run lsof to check open files
    sprintf(lsof_cmd, "lsof -p %d", getpid());
    system(lsof_cmd);

	//close(p.pipefd[0]);
	//close(p.pipefd[1]);
	close(p.infilefd);
	close(p.outfilefd);
	cleanup(&p);

	    // Run lsof to check open files
    sprintf(lsof_cmd, "lsof -p %d", getpid());
    system(lsof_cmd);
	return (0);
}
