/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:49:47 by lkilpela          #+#    #+#             */
/*   Updated: 2024/03/06 13:32:20 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <signal.h>

static void	handle_syntax(t_pipex *p)
{
	if (p->argc != 5)
		error(ERR_SYNTAX);
	if (ft_strlen(p->argv[1]) == 0 || ft_strlen(p->argv[4]) == 0)
		error(ERR_FILENAME);
	if (ft_strlen(p->argv[2]) == 0 || ft_strlen(p->argv[3]) == 0)
		error(ERR_CMD_INVALID);
}

void	setup_pipe(t_pipex *p)
{
	if (pipe(p->pipefd) == -1)
		error(ERR_PIPE);
}
void handle_sigterm(int sig) 
{
    printf("Received termination signal %d\n", sig);
    exit(1);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex		p;
	int			status;
	t_tokenize	t;

	printf("argv[1] = %s\n", argv[1]);
	signal(SIGTERM, handle_sigterm);
	signal(SIGINT, handle_sigterm);
	signal(SIGQUIT, handle_sigterm);
	signal(SIGSEGV, handle_sigterm);
	init_pipex(argc, argv, envp, &p);
	handle_syntax(&p);
	setup_pipe(&p);
	status = wait_children(&p, &t);
	if (status != 0)
	{
		cleanup(&p);
		return (status);
	}
	close(p.pipefd[0]);
    close(p.pipefd[1]);
	free(t.args);
	cleanup(&p);
	return (0);
}